## Server

- 建立URI：

```java
String BASE_URI = "http://localhost:8080";
URI uri = URI.create(BASE_URI);
```

或者

```java
URI uri = UriBuilder.fromUri("http://localhost/").port(8080).build();
```

- 建立ResourceConfig：

```java
ResourceConfig rc = new ResourceConfig().packages("com");
```

- 建立HttpServer：

```java
HttpServer httpServer = GrizzlyHttpServerFactory.createHttpServer(uri, rc);
```

## Resource

- @GET：javax.ws.rs.GET
- @Path：javax.ws.rs.Path
- @PathParam：javax.ws.rs.PathParam
- @Produces：javax.ws.rs.Produce
- MediaType：javax.ws.rs.core.MediaType

## 例子

- [create](https://github.com/gaoxinge/bible/tree/master/java/glassfish/1)
- [build](https://github.com/gaoxinge/bible/tree/master/java/glassfish/2)