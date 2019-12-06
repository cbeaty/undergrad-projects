public class DoubleQuote extends CounterState {
    private static DoubleQuote instance = null;

    private DoubleQuote() {

    }

    public static DoubleQuote getInstance() {
        if(instance == null) {
            instance = new DoubleQuote();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        context.incCode(1);
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
        context.incCode(1);
    }
    @Override
    public void backslash(StateCounter context) {
        //Need to get back to code, "Hello, \"THis is a quote in a string"" should be code
        context.incCode(1);
        context.changeState(Code.getInstance());
    }
    @Override
    public void doubleQuote(StateCounter context) {
        //End of a string, countinue to code
        context.incCode(1);
        context.changeState(Code.getInstance());
    }
}