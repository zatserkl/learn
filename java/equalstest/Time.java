package equalstest;

public class Time {
    public int hour;
    public int minute;
    public double second;

    public Time(int hour, int minute, double second) {
	this.hour = hour;
	this.minute = minute;
	this.second = second;
    }

    public Time(Time time) {
        this(time.hour, time.minute, time.second);
        System.out.println("Copy constructor Time(Time time)");
    }

    public void printTime() {
        // System.out.println("hour = " + hour + " minute = " + minute + " second = " + second);
        System.out.println(hour + ":" + minute + ":" + second);
    }
 
    // Overriding the toString of Time class
    @Override                                   // @Override is an annotation
    public String toString() {
        return hour + ":" + minute + ":" + second;
    }

    // Overriding the equals
    @Override
    public boolean equals(Object obj)
    {
        // NB: Override of equals in general requires Override of hashCode method

        // Check if they refer to the same object
        if (obj == this) return true;

        if ((obj == null) || (obj.getClass() != this.getClass())) return false;
        // similar implementation: not recommended http://www.technofundo.com/tech/java/equalhash.html
        // Check if o is an instance of Complex or not
        // "null instanceof [type]" also returns false
        // if (!(obj instanceof Time)) return false;    // not recommended

        Time time = (Time) obj;
        return (hour == time.hour) && (minute == time.minute) && (second == time.second);
    }

    @Override
    public int hashCode() {
        int result = 17;
        result = 31 * result + hour;
        result = 31 * result + minute;

        // for the double field
        long code_long_second = Double.doubleToLongBits(second);
        int code_int_second = (int) (code_long_second ^ (code_long_second >>> 32));
        result = 31 * result + code_int_second;
        return result;
    }

    public static void main(String[] args)
    {
        Time time = new Time(2, 3, 4.14);
        // time.printTime();
        System.out.println("Time.main: time = " + time);
    }
}

