public class LeavingMultiLine extends CounterState {
    private static LeavingMultiLine instance = null;

    private LeavingMultiLine() {

    }

    public static LeavingMultiLine getInstance() {
        if(instance == null) {
            instance = new LeavingMultiLine();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        //The end of a comment, get back to code
        context.incMulti(2);
        context.changeState(Code.getInstance());
    }
    @Override
    public void star(StateCounter context) {
        //multiple stars within the multiline comment, keep going
        context.incMulti(1);
    }
    @Override
    public void character(StateCounter context) {
        context.incMulti(2);
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void newLine(StateCounter context) {
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void backslash(StateCounter context) {
        context.incMulti(2);
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incMulti(2);
        context.changeState(MultiLine.getInstance());
    }
}