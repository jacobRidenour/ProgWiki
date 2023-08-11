# Local imports
from lssParsing import *
from lss import *  

# External imports
# <None>

# TODO: rewrite based on using dictionaries rather than... this mess

# Reads a .lss file and reports some information based on its contents
def read_lss_file(file_path):
    try:
        tree = ET.parse(file_path)
        file_root = tree.getroot()

        split_file = lss()
        split_file.segments = []
        
        #game_name = root.findtext('GameName', default='')
        #category_name = root.findtext('CategoryName', default='')
        #layout_path = root.findtext('LayoutPath', default='')
        #timer_offset = root.findtext('Offset', default='')

        #runs_started = count_attempts(root)
        #runs_finished = count_runs_finished(root)

        split_file.game_name = file_root.findtext('GameName', default='')
        split_file.category_name = file_root.findtext('CategoryName', default='')
        split_file.layout_path = file_root.findtext('LayoutPath', default='')
        split_file.timer_offset = file_root.findtext('Offset', default='')
        split_file.runs_started = count_attempts(file_root)
        split_file.runs_finished = count_runs_finished(file_root)
        
        print(f"Game Name:     {split_file.game_name}")
        print(f"Category Name: {split_file.category_name}")
        print(f"Layout Path:   {split_file.layout_path}")
        print(f"Timer Offset:  {split_file.timer_offset}")
        print(f"Runs Started:  {split_file.runs_started}")
        print(f"Runs Finished: {split_file.runs_finished}")
        print("\nSegments")

        sum_of_best = 0.0
        total_playtime = 0.0
        previous_split_time_seconds = 0.0
        # <Segment>
        file_segments = file_root.findall(".//Segment")
        for index, segment in enumerate(file_segments, start=1):
            # get <Segment><Name>
            name = segment.findtext('Name', default='')
            
            # get <Segment><SplitTimes>
            split_times = segment.find('SplitTimes')
            split_time_pb = get_splittime_pb(split_times, 'Personal Best')
            
            # calculate segment time in PB
            segment_time_pb = None
            if index == 1:
                segment_time_pb = split_time_pb
                previous_split_time_seconds = time_to_seconds(split_time_pb)
            else:
                pb_segment_seconds = time_to_seconds(split_time_pb)
                pb_segment_time_seconds = pb_segment_seconds - previous_split_time_seconds
                segment_time_pb = seconds_to_time(pb_segment_time_seconds)
                previous_split_time_seconds = pb_segment_seconds
            
            # get <Segment><BestSegmentTime><RealTime>
            best_segment = segment.find('BestSegmentTime')
            gold_segment_time = get_real_time(best_segment)
                        
            # get <Segment><SegmentHistory>
            segment_history = segment.find("SegmentHistory")
            #segment_history = convert_to_dictionary(segment_history)
            
            # update sum of best and total playtime
            sum_of_best += time_to_seconds(gold_segment_time)
            total_playtime += get_segment_sum(segment_history)
            
            # find the attempt whose time matches the best segment time & the date/time for that run
            gold_segment_id = get_gold_id(segment_history, gold_segment_time)
            gold_segment_date = get_attempt_date(gold_segment_id, file_root)
            
            # find the attempt and time that is slowest for this segment & the date/time for that run
            worst_segment_time = get_worst_time(segment_history)
            worst_segment_date = get_attempt_date(worst_segment_time[0], file_root)
            
            # calculate the average time for this segment, std deviation, median
            average_time = get_average_time(segment_history)
            std_dev = get_std_dev(segment_history)
            median_time = get_median_time(segment_history)
            
            # calculate how many runs completed segment compared to total number of attempts
            percent_vs_attempts = get_percent_finished(split_file.runs_started, segment_history)
            decent_percentage = get_above_average_rate(segment_history)
            
            print(f"{index}. {name}")
            print(f"    - Split Time (PB):   {split_time_pb}")
            print(f"    - Segment Time (PB): {segment_time_pb}")
            print(f"    - Gold:              {gold_segment_time}, on attempt {gold_segment_id}, which happened on {gold_segment_date[0]} at {gold_segment_date[1]}")
            print(f"    - Worst Time:        {worst_segment_time[1]}, on attempt {worst_segment_time[0]}, which happened on {worst_segment_date[0]} at {worst_segment_date[1]}")
            print(f"    - Median Time:       {median_time}")
            print(f"    - Average Time:      {average_time}")
            print(f"    - Std Deviation:     {std_dev}")
            print(f"    - This segment is completed {percent_vs_attempts} of the time.")
            print(f"    - This segment is above average {decent_percentage} of the time.")
            
            current_segment = segment_data()

            # segment_data: name, split_time_pb, segment_time_pb
            current_segment.name = name
            current_segment.split_time_pb = split_time_pb
            current_segment.segment_pb = segment_time_pb

            # segment_data: segment_gold
            current_segment.segment_gold.time = gold_segment_time
            current_segment.segment_gold.id = gold_segment_id
            current_segment.segment_gold.date_time = [gold_segment_date[0], gold_segment_date[1]]

            # segment_data: segment worst
            current_segment.segment_worst.time = worst_segment_time[1]
            current_segment.segment_worst.id = worst_segment_time[0]
            current_segment.segment_worst.date_time = [worst_segment_date[0], worst_segment_date[1]]

            # segment_data: completion percent
            current_segment.completion_pct = percent_vs_attempts
            
            # segment_data: stats
            current_segment.stats.average = average_time
            current_segment.stats.stdev = std_dev
            current_segment.stats.median = median_time
            current_segment.stats.percent_above_average = decent_percentage
            #current_segment.stats.improvement = 

            split_file.segments.append(current_segment)
        
        split_file.sob = seconds_to_time(sum_of_best)
        split_file.total_playtime = seconds_to_time(total_playtime)
        return split_file

    except (FileNotFoundError, ET.ParseError) as e:
        print(f"Error: {e}")

def main():
    while True:
        try:
            lss_file = input("Enter the path to a valid .lss file (or 'q' to quit): ")
            if lss_file.lower() == 'q' or lss_file.lower() == 'quit':
                break
            if not lss_file.lower().endswith('.lss'):
                raise ValueError('Invalid file format. File must be of type .lss')
            else:
                with open(lss_file, 'r') as file:
                    header = [file.readline() for _ in range(2)]
                    if not header[0].startswith('ï»¿<?xml version="1.0" encoding="UTF-8"?>'):
                        raise ValueError('Invalid XML version header')
                    if not header[1].strip().startswith('<Run version='):
                        raise ValueError('Missing <Run> tag.')
                read_lss_file(lss_file)
        except (FileNotFoundError, ET.ParseError, ValueError) as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    main()
