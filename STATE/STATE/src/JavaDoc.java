public class JavaDoc extends CounterState {
    private static JavaDoc instance = null;

    private JavaDoc() {

    }

    public static JavaDoc getInstance() {
        if(instance == null) {
            instance = new JavaDoc();
        }

        return instance;
    }
    @Override
    public void slash(StateCounter context) {
        context.incJava(1);
    }
    @Override
    public void star(StateCounter context) {
        //could be the end of a javadoc
        context.changeState(LeavingJavaDoc.getInstance());
    }
    @Override
    public void character(StateCounter context) {
        context.incJava(1);
    }
    @Override
    public void newLine(StateCounter context) {

    }
    @Override
    public void backslash(StateCounter context) {
        context.incJava(1);
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incJava(1);
    }
}