package com;
import java.net.URI;
import java.io.IOException;  
import org.glassfish.grizzly.http.server.HttpServer; 
import org.glassfish.jersey.server.ResourceConfig; 
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;  
  
public class HelloWorldServer {
    public static void main(String[] args) throws IOException {
        String BASE_URI = "http://localhost:8080";
        URI uri = URI.create(BASE_URI);
        ResourceConfig rc = new ResourceConfig().packages("com");
        HttpServer httpServer = GrizzlyHttpServerFactory.createHttpServer(uri, rc);   
        System.in.read();  
        httpServer.shutdown();  
        System.exit(0);  
    }  
}  