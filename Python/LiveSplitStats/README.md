# LiveSplit Stats

Reports some information and statistics gleaned from [LiveSplit](http://livesplit.org/) split (.lss) files. Only accounts for RTA (for now). Shows some information and statistics visually.

Parsed information
* Game Name
* Category Name
* Layout Path
* Timer Offset
* Runs Started
* Runs Finished
* Segment information (see below)

Segment information
* Name
* Split time in PB
* Segment time in PB
* Best time (gold), which attempt, on what date/time
* Worst time, which attempt, on what date/time
* Calculations:
    * Average time
    * Median time
    * Standard deviation
    * Completion percent
    * TODO: improvement over time

Other information
* Sum of Best segments
* TODO: Total playtime

Graphs
* Represent PB as a line, show:
    * Split time for each
    * Duration of each segment
    * Possible time save 
* Runs over time (y = runs finished duration x = attempt number)
* Seconds of improvement (pie chart of worst-best for each segment)
* CSV export
    * Parsed segment information (time in seconds)