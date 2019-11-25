import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Profiler {
    private static Profiler instance = null;
    private boolean enabled;
    private boolean called;
    private ArrayList<Duration> durationList;
    private HashMap<String, ArrayList<Duration>> timers;
    private HashMap<String, Integer> counters;
    //Making the Profiler class a singleton by having a private constructor and static getInstance()
    private Profiler() {
        this.enabled = true;
        this.called = false;
        this.durationList = new ArrayList<Duration>();
        this.timers = new HashMap<>();
        this.counters = new HashMap<>();
    }
    
    public static Profiler getInstance() {
        if (instance == null) {
            instance = new Profiler();
        }
        return instance;
    }
    
    public void start(String key) throws ProfilerException {
        if (isEnabled()) { //First check is to see if the user wants to use it
            //if called is false --> this is first instance of start, otherwise there is already a start without a stop
            if (!isCalled()) { //Second is to make sure there isn't a start followed by a start
                //If the timer already exists
                if (timers.containsKey(key)) {
                    //create a new duration
                    Duration d = new Duration();
                    //set it to the current time
                    d.setStart(System.nanoTime());
                    //make the durationlist equal to the previous list with the same key 
                    durationList = timers.get(key);
                    //add the new duration to the list
                    durationList.add(d);
                    //add the list to the hashmap
                    timers.put(key, durationList);
                }
                //If the timer is a new key, add it
                else {
                    //Create a new list of durations
                    ArrayList<Duration> dList = new ArrayList<Duration>();
                    //Create a new duration
                    Duration d = new Duration();
                    //Set the time
                    d.setStart(System.nanoTime());
                    //Add to the list
                    dList.add(d);
                    //Add the list to the hashmap
                    timers.put(key, dList);
                }
                //Make the called boolean true so that we don't have start followed by a start
                setCalled(true);
            }
            else { //Throw an exception if called is true and there is another start attempt
                throw new ProfilerException();
            }
        }
    }
    //Same as above except we add a message to every duration 
    public void start(String key, String msg) throws ProfilerException {
        if(isEnabled()) {
            if (!isCalled()) {
                if (timers.containsKey(key)) {
                    Duration d = new Duration();
                    d.setStart(System.nanoTime());
                    d.setStartMsg(msg);
                    durationList = timers.get(key);
                    durationList.add(d);
                    timers.put(key, durationList);
                }
                else {
                    ArrayList<Duration> dList = new ArrayList<Duration>();
                    Duration d = new Duration();
                    d.setStart(System.nanoTime());
                    d.setStartMsg(msg);
                    dList.add(d);
                    timers.put(key, dList);
                }
                setCalled(true);
            }
            else {
                throw new ProfilerException();
            }
        }
    }

    public void stop(String key) throws ProfilerException {
        //Check for user
        if (isEnabled()) {
            //If there is a start then when can stop, otherwise there isn't a start and throw an exception
            if (isCalled()) {
                //If there is already a key, get the previous duration, and set its stop time
                if (timers.containsKey(key)) {
                    //get the current list of timers
                    durationList = timers.get(key);
                    //Find the duration with a missing a stop
                    for (Duration d : durationList) {
                        if (d.getStop() == 0) {
                            //Set its stop
                            d.setStop(System.nanoTime());
                        }
                    }
                    //Add it the list back to the hashmap
                    timers.put(key, durationList);
                }
                else { //Trying to add a stop with new key but it doesn't match the current start
                    throw new ProfilerException();
                }
                //Set called to false so that we can create more starts
                setCalled(false);
            }
            else {
                throw new ProfilerException();
            }
        }
    }
    //Same as above, but adding a message
    public void stop(String key, String msg) throws ProfilerException {
        if (isEnabled()) {
            if (isCalled()) {
                if (timers.containsKey(key)) {
                    durationList = timers.get(key);
                    for (Duration d : durationList) {
                        if (d.getStop() == 0) {
                            d.setStop(System.nanoTime());
                            d.setStopMsg(msg);
                        }
                    }
                    timers.put(key, durationList);
                }
                else {
                    throw new ProfilerException();
                }
                setCalled(false);
            }
            else {
                throw new ProfilerException();
            }
        }
    }

    public void count(String key) {
        //Check for the user
        if (isEnabled()) {
            //if the key exists, increment it by one
            if (counters.containsKey(key)) {
                counters.put(key, counters.get(key) + 1);
            }
            //if it is new, set it to one
            else {
                counters.put(key, 1);
            } 
        }
    }

    public ArrayList<ArrayList<String>> getSurveyData() throws ProfilerException {
        //Create an 2D list for the specific survey data (Profile Name, Average Duratio, Longest Duration, Shortest Duration)
        ArrayList<ArrayList<String>> surveyData = new ArrayList<ArrayList<String>>();
        for (Map.Entry<String, ArrayList<Duration>> entry : timers.entrySet()) {
            String key = entry.getKey(); //Get the key for the 
            ArrayList<Duration> value = entry.getValue(); //Get the value for the key
            ArrayList<String> tempRow = new ArrayList<String>();
            //Add the profile name
            tempRow.add(key);
            //Get the average duration
            String avg = Long.toString(getAvgDuration(value));
            tempRow.add(avg);
            //Get the longest duration
            String longest = Long.toString(getLongestDuration(value));
            tempRow.add(longest);
            //Get the shortest duration
            String shortest = Long.toString(getShortestDuration(value));
            tempRow.add(shortest);
            //Add the column to the 2D array
            surveyData.add(tempRow);
        }
        return surveyData;
    }

    public ArrayList<ArrayList<String>> getDetailData() {
        //For (Profile Name, Start Time, Stop Time,Duration, Start Message, Stop Message)
        ArrayList<ArrayList<String>> detailData = new ArrayList<ArrayList<String>>();
        for (Map.Entry<String, ArrayList<Duration>> entry : timers.entrySet()) {
            String key = entry.getKey();
            ArrayList<Duration> value = entry.getValue();
            for(Duration d : value) { //Look through the arraylist of durations
                ArrayList<String> tempRow = new ArrayList<String>(); //Create a new array everytime
                //Add key
                tempRow.add(key); 
                //Get start
                String start = Long.toString(d.getStart());
                //Get stop
                String stop = Long.toString(d.getStop());
                //Get duration
                String duration = Long.toString(d.getStop() - d.getStart());
                //Get messages
                String startMsg = d.getStartMsg();
                String stopMsg = d.getStopMsg();
                tempRow.add(start);
                tempRow.add(stop);
                tempRow.add(duration);
                tempRow.add(startMsg);
                tempRow.add(stopMsg);
                detailData.add(tempRow);
            }
        }
        return detailData;
    }

    public ArrayList<ArrayList<String>> getCounterData() {
        //For (Name, counters)
        ArrayList<ArrayList<String>> counterData = new ArrayList<ArrayList<String>>();
        for (Map.Entry<String, Integer> entry : counters.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            ArrayList<String> tempRow = new ArrayList<String>();
            tempRow.add(key);
            tempRow.add(Integer.toString(value));
            counterData.add(tempRow);
        }
        return counterData;
    }
    //Throws exception if there is only one start and no stop
    public long getLongestDuration(ArrayList<Duration> value) throws ProfilerException {
        //Longest duration is currently the first
        Duration tempD = value.get(0);
        if (tempD.getStop() == 0) {
            throw new ProfilerException();
        }
        long longest = tempD.getStop() - tempD.getStart();
        for(Duration d : value) { //Go through the list of durations and check
            if (d.getStop() == 0) {
                throw new ProfilerException();
            }
            long duration = d.getStop() - d.getStart();
            if (duration > longest) {
                longest = duration; //Reset the longest
            }
        }
        return longest;
    }
    //Same as above except for the shortest, Throws exception if there is only one start and no stop
    public long getShortestDuration(ArrayList<Duration> value) throws ProfilerException {
        Duration tempD = value.get(0);
        if (tempD.getStop() == 0) {
            throw new ProfilerException();
        }
        long shortest = tempD.getStop() - tempD.getStart();
        for(Duration d : value) {
            if (d.getStop() == 0) {
                throw new ProfilerException();
            }
            long duration = d.getStop() - d.getStart();
            if (duration < shortest) {
                shortest = duration;
            }
        }
        return shortest;
    }
    //Throws exception if there is only one start and no stop
    public long getAvgDuration(ArrayList<Duration> value) throws ProfilerException {
        long avg = 0;
        long size = value.size();
        for(Duration d : value) {
            if (d.getStop() == 0) { 
                throw new ProfilerException();
            }
            avg += d.getStop() - d.getStart(); //Sum all the durations
        }
        if (size != 0) { //Make sure we aren't dividing by zero
            return avg / size; //Get average
        }
        else {
            return 0;
        }
    }
    //Getters and setters for the enabled bool
    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public boolean isEnabled() {
        return enabled;
    }
    //getting and setting the called, private so that users can't mess up the start and stops
    private boolean isCalled() {
        return this.called;
    }

    private void setCalled(boolean called) {
        this.called = called;
    }
    //Make the GUI when called
    public void generateReport() throws ProfilerException {
        ProfilerGUI gui = new ProfilerGUI();
    }
}