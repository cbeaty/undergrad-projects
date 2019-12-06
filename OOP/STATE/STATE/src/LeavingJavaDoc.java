public class LeavingJavaDoc extends CounterState {
    private static LeavingJavaDoc instance = null;

    private LeavingJavaDoc() {

    }

    public static LeavingJavaDoc getInstance() {
        if(instance == null) {
            instance = new LeavingJavaDoc();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        //End of javadoc, get back to code
        context.incJava(2);
        context.changeState(Code.getInstance());
    }
    @Override
    public void star(StateCounter context) {
        //Multiple stars, keep going
        context.incJava(1);
    }
    @Override
    public void character(StateCounter context) {
        context.incJava(2);
        context.changeState(JavaDoc.getInstance());
    }
    @Override
    public void newLine(StateCounter context) {
        context.incJava(1);
        context.changeState(JavaDoc.getInstance());
    }
    @Override
    public void backslash(StateCounter context) {
        context.incJava(2);
        context.changeState(JavaDoc.getInstance());
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incJava(2);
        context.changeState(JavaDoc.getInstance());
    }
}