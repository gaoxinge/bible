package com;
import java.net.URI;
import javax.ws.rs.core.UriBuilder;
import org.glassfish.grizzly.http.server.HttpServer;
import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;

public class HelloWorldServer {
    public static void main(String[] args) throws Exception {
        URI uri = UriBuilder.fromUri("http://localhost/").port(8080).build();
        ResourceConfig rc = new ResourceConfig().packages("com");
        HttpServer httpServer = GrizzlyHttpServerFactory.createHttpServer(uri, rc);
        System.in.read();
        httpServer.stop();
    }
}