package nonweb;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class Comp {
    
    @Bean
    public TestBean testBean() {
        return new TestBean();
    }
}