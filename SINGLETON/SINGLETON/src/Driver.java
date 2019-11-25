public class Driver {
    public static void main(String[] args) {
        try
        {
            //build up a series of calls to start and stop
            for(int i = 0;i < 100;i++)
            {
                Profiler.getInstance().start("timer1", "start of timer, i: " + i);

                //pause the program for 100 ms
                Thread.sleep(100);

                Profiler.getInstance().stop("timer1", "end of timer, i: " + i);

                //if the counter is an even multiple of 10
                if(i % 10 == 0)
                {
                    //count how many times the counter is an even multiple of 10
                    Profiler.getInstance().count("every 10 count");
                }
            }

            //turn off the profiler
            Profiler.getInstance().setEnabled(false);

            Profiler.getInstance().start("not really a timer");

            Profiler.getInstance().count("every 10 count");
            Profiler.getInstance().count("every 10 count");
            Profiler.getInstance().count("every 10 count");

            Thread.sleep(100);

            Profiler.getInstance().stop("not really a timer");

            //turn the profiler back on
            Profiler.getInstance().setEnabled(true);

            //choose a random amount of time between 0 - 5 sec
            Profiler.getInstance().start("random timer");

            //Math.random() returns a random double between 0.0-1.0 
            Thread.sleep((long)(Math.random() * 5000));

            Profiler.getInstance().stop("random timer");

            //analyze the results of the profiler
            Profiler.getInstance().generateReport();
        }
        catch(ProfilerException ex1)
        {
            ex1.printStackTrace();
        }
        catch(InterruptedException ex2)
        {
            ex2.printStackTrace();
        }
    }
}