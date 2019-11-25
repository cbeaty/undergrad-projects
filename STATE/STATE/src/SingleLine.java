public class SingleLine extends CounterState {
    private static SingleLine instance = null;

    private SingleLine() {

    }

    public static SingleLine getInstance() {
        if(instance == null) {
            instance = new SingleLine();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        context.incSingle(1);
    }
    @Override
    public void star(StateCounter context) {
        context.incSingle(1);
    }
    @Override
    public void character(StateCounter context) {
        context.incSingle(1);
    }
    @Override
    public void newLine(StateCounter context) {
        //Only case where the single line will be over
        context.changeState(Code.getInstance());
    }
    @Override
    public void backslash(StateCounter context) {
        context.incSingle(1);
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incSingle(1);
    }
}