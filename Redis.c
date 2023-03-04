

#include <stdlib.h>
#include "hiredis/hiredis.h"





typedef struct product{
    int product_id;
    char *product_code;
    int quatity;
    int price;
} product;

typedef struct supplier{
    int supplier_id;
    char *name;
    int phone;
} supplier;

typedef struct productSupplier{
    product prod;
    supplier supl;
} productSupplier;

typedef struct order{
    int order_id;
    int product_id;
    int quantity;
}


// add a product into redis, the product code is the key for the hash.
void add_product_to_redis(redisContext c, redisReply reply, product prod){

    reply = redisCommand(c,"HMSET", prod.product_code, "id", prod.product_id, "quantity", prod.quatity, "price", prod.price );

}

void add_supplier_to_redis(redisContext c, redisReply reply, supplier supl){

    reply = redisCommand(c,"HMSET", supl.name, "id", supl.supplier_id, "phone", supl.phone);
}

// assosiats a product to a supplier, a supplier can have mutiple products
void add_prodSupl_to_redis(redisContext c, redisReply reply, productSupplier ps){
    
    reply = redisCommand(c,"HSET", ps.supl.supplier_id,   )
}


int main(int argc, char **argv[]){
    const char *hostname = "127.0.0.7";
    int port = 6379;

redisContext *c = redisConnect(hostname, port);
if (c != NULL && c->err) {
    printf("Error: %sn", c->errstr);
    // handle error
} else {
    printf("Connected to Redisn");
}


redisReply *reply;
reply = redisCommand(c, "SET %s %s", "foo", "bar");

freeReplyObject(reply);



redisFree(c);
}
