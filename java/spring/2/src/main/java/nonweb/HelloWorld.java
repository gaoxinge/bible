package nonweb;
import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class HelloWorld implements CommandLineRunner {
    
    @Autowired
    private BeanFactory bf;
    
    @Autowired
    private Comp comp;
    
    @Override
    public void run(String... args) {
        System.out.println((Comp) bf.getBean("Comp"));
        System.out.println(comp);
    }
    
    public static void main(String[] args) {
        SpringApplication.run(HelloWorld.class, args).close();
    }
}