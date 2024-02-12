require 'date'

# Conversion of root/Ada/MonthYear.cpp to Ruby.

# class to represent calendar dates
class DMY
  attr_accessor :day, :month, :year

  def initialize(day, month, year)
    @day = day
    @month = month
    @year = year
  end

  # note Ruby doesn't have an enum type
  # map the name of a month to its symbolic representation
  def self.month_name(month)
    months = [
      :January, :February, :March, :April, :May, :June,
      :July, :August, :September, :October, :November, :December
    ]
    months[month - 1]
  end

  # print the date
  def print_date
    puts "#{DMY.month_name(@month)} #{@day}, #{@year}"
  end

  # compute and print months from now
  def print_months_from_now
    months_from_now = (@month - Date.today.month).abs
    puts "The given date is in #{DMY.month_name(@month)} which is #{months_from_now} months from now."
  end
end

# get the current date
def get_current_date
  now = Date.today
  DMY.new(now.day, now.month, now.year)
end

# like python's if __name__ == '__main__'
if __FILE__ == $0
  # Declare and initialize date1
  date1 = DMY.new(13, 2, 1927) # 13 feb 1927

  # Declare and initialize date2
  date2 = DMY.new(11, 11, 2024) # 11 nov 2024

  # Print the dates
  date1.print_date
  date2.print_date

  # Compute and Print results
  date2.print_months_from_now
end
