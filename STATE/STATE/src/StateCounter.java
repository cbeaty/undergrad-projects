public class StateCounter {
    private int singleCommentCount;
    private int multiCommentCount;
    private int javadocCommentCount;
    private int codeCount;
    private CounterState currentState;

    public StateCounter(String content) {
        singleCommentCount = 0;
        multiCommentCount = 0;
        javadocCommentCount = 0;
        codeCount = 0;

        currentState = Code.getInstance();
        //Changes the current state based on the character in the content array
        for (char c : content.toCharArray()) {
            if (c == '/') {
                currentState.slash(this);
            }
            else if (c == '*') {
                currentState.star(this);
            }
            else if (c == '\n') {
                currentState.newLine(this);
            }
            else if (c == '\\' ) {
                currentState.backslash(this);
            }
            else if (c == '"') {
                currentState.doubleQuote(this);
            }
            else if (c == '\r') {
                //do nothing, stupid microsoft
            }
            else {
                currentState.character(this);
            }
        }
    }
    //THis method is needed to change the state 
    public void changeState(CounterState newState) {
        currentState = newState;
    }
    //Increments the value of specific comment with desired amount
    public void incSingle(int val) {
        singleCommentCount +=val;
    }

    public void incMulti(int val) {
        multiCommentCount += val;
    }

    public void incJava(int val) {
        javadocCommentCount += val;
    }

    public void incCode(int val) {
        codeCount += val;
    }
    //Used in the GUI to get the final comment amounts
    public int getSingle() {
        return this.singleCommentCount;
    }

    public int getMulti() {
        return this.multiCommentCount;
    }

    public int getJava() {
        return this.javadocCommentCount;
    }

    public int getCode() {
        return this.codeCount;
    }
}