# Local imports
from lssParsing import *

# External imports
# <None>

# Reads a .lss file and reports some information based on its contents
def read_lss_file(file_path):
    try:
        tree = ET.parse(file_path)
        root = tree.getroot()

        game_name = root.findtext('GameName', default='')
        category_name = root.findtext('CategoryName', default='')
        layout_path = root.findtext('LayoutPath', default='')
        timer_offset = root.findtext('Offset', default='')

        runs_started = count_attempts(root)
        runs_finished = count_runs_finished(root)

        print(f"Game Name:     {game_name}")
        print(f"Category Name: {category_name}")
        print(f"Layout Path:   {layout_path}")
        print(f"Timer Offset:  {timer_offset}")
        print(f"Runs Started:  {runs_started}")
        print(f"Runs Finished: {runs_finished}")
        print("\nSegments")

        previous_split_time_seconds = 0
        # <Segment>
        segments = root.findall(".//Segment")
        for index, segment in enumerate(segments, start=1):
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
            
            # find the attempt whose time matches the best segment time & the date/time for that run
            gold_segment_id = get_gold_id(segment_history, gold_segment_time)
            gold_segment_date = get_attempt_date(gold_segment_id, root)
            
            # find the attempt and time that is slowest for this segment & the date/time for that run
            worst_segment_time = get_worst_time(segment_history)
            worst_segment_date = get_attempt_date(worst_segment_time[0], root)
            
            # calculate the average time for this segment
            average_time = get_average_time(segment_history)
            
            # calculate the standard deviation for this segment
            std_dev = get_std_dev(segment_history)
            
            print(f"{index}. {name}")
            print(f"    - Split Time (PB):   {split_time_pb}")
            print(f"    - Segment Time (PB): {segment_time_pb}")
            print(f"    - Gold:              {gold_segment_time}, on attempt {gold_segment_id}, which happened on {gold_segment_date[0]} at {gold_segment_date[1]}")
            print(f"    - Worst Time:        {worst_segment_time[1]}, on attempt {worst_segment_time[0]}, which happened on {worst_segment_date[0]} at {worst_segment_date[1]}")
            print(f"    - Average Time:      {average_time}")
            print(f"    - Std Deviation:     {std_dev}")

    except (FileNotFoundError, ET.ParseError) as e:
        print(f"Error: {e}")

def main():
    while True:
        file_path = input("Enter the path to a valid .lss file (or 'q' to quit): ")
        if file_path.lower() == 'q' or file_path.lower() == 'quit':
            break
        read_lss_file(file_path)

if __name__ == "__main__":
    main()
