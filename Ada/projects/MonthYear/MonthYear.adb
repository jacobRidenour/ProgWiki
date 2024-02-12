-- sample program for Ada, converted by ChatGPT from the C++ version in MonthYear.cpp & initially corrected by Prasanna Suresh at Purdue Fort Wayne
-- modified by Jacob Ridenour

with Ada.Text_IO; use Ada.Text_IO;

procedure MonthYear is
   -- An enumeration type for the months of the year
   type Months_Of_The_Year is (January, February, March, April, May, June,
                                July, August, September, October, November, December);

   -- A record type to represent calendar dates
   type Date_Record is record
      Day : Integer;
      Month : Months_Of_The_Year;
      Year : Integer;
   end record;

    -- Declare an access type for Date_Record
    type Date_Record_Access is access Date_Record;

   -- Declare and initialize date1
   Date1 : Date_Record := (Day => 13, Month => February, Year => 2024);

   -- Declare and initialize date2
   Date2 : Date_Record_Access := new Date_Record'(Day => 11, Month => November, Year => 2024);
   
   Current : Date_Record := (Day => 13, Month => February, Year => 2024);

   -- Function to calculate the number of months between two dates
   function Months_Between(Date1, Date2 : Date_Record) return Integer is
    Months_In_Year : constant Integer := 12;
    Base_Year : constant Integer := 2024; -- We assume a base year for calculations
    
    Date1_Months : constant Integer :=(Date1.Year - Base_Year) * Months_In_Year + Months_Of_The_Year'Pos(Date1.Month);
    Current_Months : constant Integer :=(Current.Year - Base_Year) * Months_In_Year + Months_Of_The_Year'Pos(Current.Month);
    
    Months_Difference : Integer;
begin
    Months_Difference := Date1_Months - Current_Months;
    return Months_Difference;
end Months_Between;

begin
   -- Print results
   Put_Line(Months_Of_The_Year'Image(Date1.Month) & " " & Integer'Image(Date1.Day) & ", " & Integer'Image(Date1.Year));
   
   if (Months_Between(Date1, Current) < 0)
    then Put_Line("Date is in the past");
    else Put_Line("Date is not in the past");
    end if;
end MonthYear;