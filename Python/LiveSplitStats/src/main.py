# Locals
from lssParser import *

# TODO:
# fix best segment and worst segment parsing
# add .txt output
# graphs
# add .csv output with options

# prompts the user for a .lss file, then directs them on what to do with the parsed info (choose_option())
def main():
    while True:
        try:
            lss_file = input('Enter the path to a valid .lss file (or "q" to quit): ')
            # check if user wants to quit
            if lss_file.lower() == 'q' or lss_file.lower() == 'quit':
                break
            # make sure it's a .lss file
            if not lss_file.lower().endswith('.lss'):
                raise ValueError('Invalid file format. File must be of type .lss')
            else:
                # check first two lines 
                with open(lss_file, 'r') as file:
                    header = [file.readline() for _ in range(2)]
                    if not header[0].startswith('ï»¿<?xml version="1.0" encoding="UTF-8"?>'):
                        raise ValueError('Invalid XML version header')
                    if not header[1].strip().startswith('<Run version='):
                        raise ValueError('Missing <Run> tag.')
                result = open_lss_file(lss_file)
                if result:
                    split_data = read_lss_file(result)
                    
                    # call new options function, let user choose what they want to do with the data
                    choose_option(split_data)
                else:
                    print('Failed to open', lss_file)
                    
        except (FileNotFoundError, ET.ParseError, ValueError) as e:
            print(f'Error: {e}')

# prompts the user on what to do with parsed .lss data
def choose_option(split_data):
    print('Choose from 1 of the following options (or "q" to choose another file):')
    print('1 - print statistics and data parsed from the .lss file')
    print('2 - print statistics and data parsed from the .lss file, output results to text file')
    print('3 - show graphs based on statistics and data parsed from the .lss file')
    print('4 - output PB split times to a .csv file')
    while True:
        try:
            choice = input('Enter your choice: ')
            if choice.lower() == 'q' or choice.lower() == 'quit':
                break
            if choice == '1':
                print_parsed_info(split_data, False)
            if choice == '2':
                print_parsed_info(split_data, True)
            if choice == '3':
                print()
            if choice == '4':
                print()
            else:
                raise ValueError
        except ValueError as e:
            print(f'Error: choice must be in range [1, 4], enter "q" to choose another file.')
    
# prints data collected and calculated from the .lss file. if write_to_file flag is set, outputs to text file too.
def print_parsed_info(split_file, write_to_file):
    if write_to_file:
        print()
    
    print(f'Game Name:      {split_file.game_name}')
    print(f'Category Name:  {split_file.category_name}')
    print(f'Layout Path:    {split_file.layout_path}')
    print(f'Timer Offset:   {split_file.timer_offset}')
    print(f'Runs Started:   {split_file.runs_started}')
    print(f'Runs Finished:  {split_file.runs_finished}')
    print(f'Total Runtime:  {split_file.total_runtime}')
    print(f'Total Playtime: {split_file.total_playtime}')
    print('\nSegments')
    
    for index, current_segment in enumerate(split_file.segments, start=1):
        print(f"{index}. {current_segment.name}")
        print(f"    - Split Time (PB):   {current_segment.split_time_pb}")
        print(f"    - Segment Time (PB): {current_segment.segment_pb}")
        print(f"    - Best Time:         {current_segment.segment_gold.time}, on attempt {current_segment.segment_gold.id}, which started on {current_segment.segment_gold.date} at {current_segment.segment_gold.time}.")
        print(f"    - Worst Time:        {current_segment.segment_worst.time}, on attempt {current_segment.segment_worst.id}, which started on {current_segment.segment_worst.date} at {current_segment.segment_worst.time}.")
        print(f"    - Average Time:      {current_segment.stats.average}")
        print(f"    - Median Time:       {current_segment.stats.median}")
        print(f"    - Std Deviation:     {current_segment.stats.stdev}")
        print(f"    - This segment is completed {current_segment.stats.finished_rate} of the time.")
        print(f"    - This segment is above average {current_segment.stats.decent_rate} of the time.\n")

if __name__ == '__main__':
    main()
