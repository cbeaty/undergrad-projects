public class EnteringComment extends CounterState {
    private static EnteringComment instance = null;

    private EnteringComment() {

    }

    public static EnteringComment getInstance() {
        if(instance == null) {
            instance = new EnteringComment();
        }

        return instance;
    }
    /*Here the cases we care about are slash for singleline, star for multi or 
    javadoc and quote*/

    @Override
    public void slash(StateCounter context) {
        context.incSingle(2);
        context.changeState(SingleLine.getInstance());
    }
    @Override
    public void star(StateCounter context) {
        context.changeState(EnteringStar.getInstance());
    }
    @Override
    public void character(StateCounter context) {
        context.incCode(2);
        context.changeState(Code.getInstance());
    }
    @Override
    public void newLine(StateCounter context) {
        context.changeState(Code.getInstance());
    }
    @Override
    public void backslash(StateCounter context) {
        context.incCode(2);
        context.changeState(Code.getInstance());
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incCode(2);
        context.changeState(Code.getInstance());
    }
}