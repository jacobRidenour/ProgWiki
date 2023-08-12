# Imports
from dataclasses import dataclass, field

@dataclass
class segment_stats:
    average: str = ''
    stdev: str = ''
    decent_rate: str = ''
    finished_rate: str = ''
    median: str = ''
    improvement_over_time: str = ''

@dataclass
class segment_time:
    time: str = ''
    id: str = ''
    run_date: str = ''
    run_time: str = ''

@dataclass
class segment_data:
    name: str = ''
    split_time_pb: str = ''
    segment_pb: segment_time = field(default_factory=segment_time)
    segment_gold: segment_time = field(default_factory=segment_time)
    segment_worst: segment_time = field(default_factory=segment_time)
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
    total_runtime: str = ''
    total_playtime: str = ''
    
