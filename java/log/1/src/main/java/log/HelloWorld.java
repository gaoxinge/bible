package log;
import org.apache.log4j.Logger;

public class HelloWorld {
    private static final Logger logger = Logger.getLogger(HelloWorld.class);
    public static void main(String [] args) {
        logger.info("Hello World!");
    }
}