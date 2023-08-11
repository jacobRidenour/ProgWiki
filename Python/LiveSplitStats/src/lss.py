from dataclasses import dataclass, field

@dataclass
class segment_stats:
    average: str = ''
    stdev: str = ''
    percent_above_average: str = ''
    median: str = ''
    improvement_over_time: str = ''

@dataclass
class segment_time:
    time: str = ''
    id: str = ''
    date_time: list = field(default_factory=list)

@dataclass
class segment_data:
    name: str = ''
    split_time_pb: str = ''
    segment_pb: segment_time = field(default_factory=segment_time)
    segment_gold: segment_time = field(default_factory=segment_time)
    segment_worst: segment_time = field(default_factory=segment_time)
    completion_pct: str = ''
    stats: segment_stats = field(default_factory=segment_stats)       
        
@dataclass
class lss:
    game_name: str = ''
    category_name: str = ''
    layout_path: str = ''
    timer_offset: str = ''
    
    runs_started: int = 0
    runs_finished: int = 0
    
    # completion percentage
    completed: float = 0.0
    
    # list of segments
    segments: list = field(default_factory=list)
    
    # sum of best, total playtime
    sob: str = ''
    total_playtime: str = ''
    

# def calc_completed(runs_started, runs_finished):
#     return '{:.2f}%'.format(runs_started/runs_finished*100)
    
