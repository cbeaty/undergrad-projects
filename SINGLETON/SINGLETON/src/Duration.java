public class Duration {
    private long startTime;
    private long stopTime;
    private String startMsg;
    private String stopMsg;   
    //Initialize everything
    public Duration() {
        long startTime = 0;
        long stopTime = 0;
        String startMsg = "";
        String stopMsg = "";   
    }
    //Getters and setters for all data
    public void setStart(long startTime) {
        this.startTime = startTime;
    }

    public long getStart() {
        return this.startTime;
    }

    public void setStop(long stopTime) {
        this.stopTime = stopTime;
    }

    public long getStop() {
        return this.stopTime;
    }

    public void setStartMsg(String startMsg) {
        this.startMsg = startMsg;
    }

    public String getStartMsg() {
        return this.startMsg;
    }

    public void setStopMsg(String stopMsg) {
        this.stopMsg = stopMsg;
    }

    public String getStopMsg() {
        return this.stopMsg;
    }
}