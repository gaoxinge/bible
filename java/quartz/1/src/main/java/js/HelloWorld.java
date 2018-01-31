package js;

import org.quartz.*;
import org.quartz.impl.StdSchedulerFactory;
import static org.quartz.SimpleScheduleBuilder.simpleSchedule;
import static org.quartz.JobBuilder.newJob;
import static org.quartz.TriggerBuilder.newTrigger;

public class HelloWorld {
    
    public static void main(String[] args) throws SchedulerException {
        SchedulerFactory sf = new StdSchedulerFactory();
        Scheduler scheduler = sf.getScheduler();
        
        JobDetail job = newJob(RAMJob.class)
                        .withIdentity("job", "group")
                        .build();
                        
        Trigger trigger = newTrigger()
                          .withIdentity("trigger", "group")
                          .withSchedule(simpleSchedule().withIntervalInSeconds(1).repeatForever())
                          .startNow()
                          .build();
                          
        scheduler.scheduleJob(job, trigger);
        scheduler.start();
    }
}