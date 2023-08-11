# Standard imports
import xml.etree.ElementTree as ET
from datetime import timedelta
from math import sqrt

# retrieves the total number of attempts that have been finished (those with a <RealTime> element)
def count_runs_finished(root):
    attempts = root.findall(".//AttemptHistory/Attempt[RealTime]")
    return len(attempts)

# retrieves the total number of attempts 
def count_attempts(root):
    attempts = root.findall(".//AttemptHistory/Attempt")
    return len(attempts)

# retrieves <RealTime> under element
def get_real_time(element):
    real_time_element = element.find('RealTime')
    if real_time_element is None:
        return ''
    else:
        return real_time_element.text

# retrieves <SplitTimes><SplitTime name="Personal Best">
def get_splittime_pb(element, name):
    split_time = element.find(f"SplitTime[@name='{name}']")
    if split_time is not None:
        real_time_element = split_time.find('RealTime')
        return real_time_element.text if real_time_element is not None else ''
    return ''

# retrieves the first number from <Time id="number"> where <RealTime> matches gold_time
def get_gold_id(segment_history, gold_time):
    gold_time_id = None
    
    if segment_history is not None:
        times = segment_history.findall('Time')
        for time in times:
            real_time = get_real_time(time)
            if real_time == gold_time:
                gold_time_id = time.get('id')
                break
            
    if gold_time_id is None:
        return ''
    else:
        return gold_time_id

# retrieves the number from <Time id="number"> where <RealTime> is largest, also returns <RealTime>
def get_worst_time(segment_history):
    worst_time = '00:00:00'
    worst_time_id = -1
    
    if segment_history is not None:
        times = segment_history.findall('Time')
        for time in times:
            real_time = get_real_time(time)
            if real_time > worst_time:
                worst_time = real_time
                worst_time_id = time.get('id')
                
    return [worst_time_id, worst_time]

# retrieves the number from <Time id="number"> where <RealTime> is smallest, also returns <RealTime>
def get_best_time(segment_history):
    best_time = '99:99:99'
    best_time_id = -1
    
    if segment_history is not None:
        times = segment_history.findall('Time')
        for time in times:
            real_time = get_real_time(time)
            if real_time < best_time:
                best_time = real_time
                best_time_id = time.get('id')
                
    return [best_time_id, best_time]

# return total time spend on a given segment
def get_segment_sum(element):
    total = 0.0
    
    if element is not None:
        times = element.findall('Time')
        for time in times:
            real_time_seconds = time_to_seconds(get_real_time(time))
            total += real_time_seconds
    return total

# convert .lss <RealTime> to seconds
def time_to_seconds(time_str):
    if time_str == '':
        return 0
    parts = time_str.split(':')
    hours, minutes, seconds = int(parts[0]), int(parts[1]), float(parts[2])
    return hours * 3600 + minutes * 60 + seconds

# convert seconds to .lss <RealTime> format HH:MM:SS.ms
def seconds_to_time(seconds):
    if seconds == 0:
        return "00:00:00.0000000"
    else:
        time_obj = timedelta(seconds=seconds)
        hours, remainder = divmod(time_obj.seconds, 3600)
        minutes, seconds = divmod(remainder, 60)
        return "{:02}:{:02}:{:05.2f}".format(hours, minutes, seconds + time_obj.microseconds / 1000000)

# calculate the average time of a segment
def get_average_time(segment_history):    
    if segment_history is None:
        return ''
    
    total = 0.0
    count = 0
    
    times = segment_history.findall('Time')
    for time in times:
        real_time = get_real_time(time)
        # check real_time not empty
        if real_time:
            total += time_to_seconds(real_time)
            count += 1
    
    if count == 0:
        return ''
    
    average_in_seconds = total / count
    return seconds_to_time(average_in_seconds)

# calculate the median time for a segment
def get_median_time(segment_history):
    if segment_history is None:
        return ''

    times = segment_history.findall('Time')
    time_list = []

    for time in times:
        real_time = get_real_time(time)
        if real_time:
            time_list.append(time_to_seconds(real_time))

    if not time_list:
        return ''

    time_list.sort()
    n = len(time_list)

    # even number of times
    if n % 2 == 0:
        middle1 = time_list[n // 2 - 1]
        middle2 = time_list[n // 2]
        median_in_seconds = (middle1 + middle2) / 2
    # odd number of times
    else:
        median_in_seconds = time_list[n // 2]

    return seconds_to_time(median_in_seconds)

# calculate standard deviation for a segment
def get_std_dev(segment_history):
    if segment_history is None or not segment_history.findall('Time'):
        return ''
    
    # get all times in seconds for ease of maths
    times_in_seconds = [time_to_seconds(get_real_time(time)) for time in segment_history.findall('Time')]
    
    # get the average
    mean_time = sum(times_in_seconds) / len(times_in_seconds)
    
    # get squared deltas from mean
    squared_deltas = [(time - mean_time) ** 2 for time in times_in_seconds]
    
    # get mean of squared deltas
    variance = sum(squared_deltas) / len(squared_deltas)
    
    # take the square root to get std dev
    std_dev_seconds = sqrt(variance)
    
    return seconds_to_time(std_dev_seconds)

# count number of above average runs
def get_above_average_rate(segment_history):
    if segment_history is None:
        return 0
    
    average_time = get_average_time(segment_history)
    if not average_time:
        return 0
    
    above_average_count = 0
    times = segment_history.findall('Time')
    
    for time in times:
        real_time = get_real_time(time)
        if real_time:
            time_seconds = time_to_seconds(real_time)
            if time_seconds < time_to_seconds(average_time):
                above_average_count += 1
    
    segment_count = 0
    for _ in segment_history.findall("Time"):
        segment_count += 1
    
    #'{:.2f}%'.format(decent)
    
    decent = (above_average_count / segment_count)*100
    
    return '{:.2f}%'.format(decent)

# find the attempt that matches a given time (used for golds/worst segments currently)
def get_attempt_date(attempt_id, root):
    # find attempt with matching ID
    attempt_element = root.find(f"./AttemptHistory/Attempt[@id='{attempt_id}']")
    
    # extract the started="" attribute
    if attempt_element is not None:
        result = attempt_element.get('started')
        result = result.split(' ')
        return result
    else:
        return ''

# simple - looks at number of completed segments vs. attempts
def get_percent_finished(attempts, segment_history):
    completed_segments = len(segment_history.findall('Time'))
    if completed_segments == 0:
        return '? %'
    finished_percent = ((completed_segments/attempts))*100
    return '{:.2f}%'.format(finished_percent)

def convert_to_dictionary(segment_history_element):
    time_dict = {}
    
    # Iterate through the Time elements in the SegmentHistory
    for time_element in segment_history_element.findall("Time"):
        time_id = int(time_element.get("id"))  # Get the value of the id attribute
        real_time = get_real_time(time_element)  # Assuming you have a function to get RealTime
        
        # Add the entry to the dictionary
        time_dict[time_id] = real_time
    
    return time_dict
