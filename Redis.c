

#include <stdlib.h>
#include "hiredis/hiredis.h"


// welcome you all. this the the program for communication with a redis server
/*
I have outline some functions that are need to be filed in. 

IMPORTANT desinge decisions:
products are stored with  "product code" as key
supplieras are stored with  "name" as key
productsupplier are stored with "supplier_id" as key
orders are stored with "order_id" as key

to search for which prod a supl has you search for the name in the function, then the funtion find the supl_id and get with that.

updating is straight forward, just use HSET I think

remove/delete: maybe just delete 


Axel takes the hiredis functions.


FOR THE UNINITIATED in hiredis and redis: (if you dont have to time to learn it)
maybe we should create functions that first creates (a from example) prod on the stack, and then add that it to redis,
so that we dont have to manually add them. 
also for update and delete. 

if you feel really fancy it would be great to have a menu as in ioopm wearhouse, maybe we could just steal that code. 
*/


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
