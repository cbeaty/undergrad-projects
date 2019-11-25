public class MultiLine extends CounterState {
    private static MultiLine instance = null;

    private MultiLine() {

    }

    public static MultiLine getInstance() {
        if(instance == null) {
            instance = new MultiLine();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        context.incMulti(1);
    }
    @Override
    public void star(StateCounter context) {
        //Check for leaving the multiline case
        context.changeState(LeavingMultiLine.getInstance());
    }
    @Override
    public void character(StateCounter context) {
        context.incMulti(1);
    }
    @Override
    public void newLine(StateCounter context) {
        
    }
    @Override
    public void backslash(StateCounter context) {
        context.incMulti(1);
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incMulti(1);
    }
}