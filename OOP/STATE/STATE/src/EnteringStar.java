public class EnteringStar extends CounterState {
    private static EnteringStar instance = null;

    private EnteringStar() {

    }

    public static EnteringStar getInstance() {
        if(instance == null) {
            instance = new EnteringStar();
        }

        return instance;
    }
    /*The two cases we care about are between the multiline and the javadoc */
    @Override
    public void slash(StateCounter context) {
        context.incMulti(3);
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void star(StateCounter context) {
        context.incJava(3);
        context.changeState(JavaDoc.getInstance());
    }
    @Override
    public void character(StateCounter context) {
        context.incMulti(3);
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void newLine(StateCounter context) {

    }
    @Override
    public void backslash(StateCounter context) {
        context.incMulti(3);
        context.changeState(MultiLine.getInstance());
    }
    @Override
    public void doubleQuote(StateCounter context) {
        context.incMulti(3);
        context.changeState(MultiLine.getInstance());
    }
}