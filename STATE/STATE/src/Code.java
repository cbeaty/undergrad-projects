public class Code extends CounterState {
    private static Code instance = null;

    private Code() {

    }

    public static Code getInstance() {
        if(instance == null) {
            instance = new Code();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        //If in code and we encounter a / it could be a comment
        context.changeState(EnteringComment.getInstance());
    }
    @Override
    public void star(StateCounter context) {
        context.incCode(1);
    }
    @Override
    public void character(StateCounter context) {
        context.incCode(1);
    }
    @Override
    public void newLine(StateCounter context) {
    
    }
    @Override
    public void backslash(StateCounter context) {
        context.incCode(1);
    }
    @Override
    public void doubleQuote(StateCounter context) {
        //This is used to chech for the quotes, which without this state would through a fit
        //for the case where " // test" is in a string a should be could
        context.incCode(1);
        context.changeState(DoubleQuote.getInstance());
    }
}