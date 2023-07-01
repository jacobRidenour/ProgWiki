import xml.etree.ElementTree as ET

def get_real_time(element):
    real_time_element = element.find('RealTime')
    return real_time_element.text if real_time_element is not None else ''

def count_attempts(root):
    attempts = root.findall(".//AttemptHistory/Attempt")
    return len(attempts)

def count_runs_finished(root):
    attempts = root.findall(".//AttemptHistory/Attempt[RealTime]")
    return len(attempts)

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

        segments = root.findall(".//Segment")
        for index, segment in enumerate(segments, start=1):
            name = segment.findtext('Name', default='')
            best_segment_time = segment.find('BestSegmentTime')
            gold_real_time = get_real_time(best_segment_time)
            
            print(f"{index}. {name}")
            print(f"    - Gold: {gold_real_time}")

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
