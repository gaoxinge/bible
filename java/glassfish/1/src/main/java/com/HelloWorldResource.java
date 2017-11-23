package com; 
import javax.ws.rs.GET;  
import javax.ws.rs.Path;  
import javax.ws.rs.Produces;  
  
@Path("/")  
public class HelloWorldResource {
    @GET  
    @Produces("text/plain")  
    public String sayHelloWorld() {  
        return "Hello World!";  
    }  
}  