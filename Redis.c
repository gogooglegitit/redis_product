



#include <stdlib.h>
#include "hiredis/hiredis.h"
#include <string.h>


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
    product *prod;
    supplier *supl;
} productSupplier;

typedef struct order{
    int order_id;
    int product_id;
    int quantity;
} order;


// add a product into redis, the product code is the key for the hash.
void add_product_to_redis(redisContext *c, redisReply *reply, product *prod){

    reply = redisCommand(c,"HMSET %s %s %d %s %d %s %d", prod->product_code, "id", prod->product_id, "quantity", prod->quatity, "price", prod->price );

}

void add_supplier_to_redis(redisContext *c, redisReply *reply, supplier *supl){

    reply = redisCommand(c,"HMSET %s %s %d %s %d", supl->name, "id", supl->supplier_id, "phone", supl->phone);
}

// assosiats a product to a supplier, a supplier can have mutiple products
void add_prodSupl_to_redis(redisContext *c, redisReply *reply, productSupplier *ps, char * number){
    
    // char *number_to_add;

    // //get the number of fields in this key;
    // reply = redisCommand(c, "HLEN %d", ps->supl->supplier_id );
    // printf("passed on read \n");
    // printf("%d \n", reply->type);
    // printf("%d \n", reply->integer);

    // if (reply == NULL || reply->type == REDIS_REPLY_NIL ){
    //     number_to_add = "0";
    // }
    // else{
    //     printf("in else \n");
    //     number_to_add =  reply->integer;
    // }
    // printf("passed on assign to add_to \n");

    // printf("%d\n", number_to_add);

    // char prod_number[20] = "product n.";

    // strcat(prod_number, number_to_add);

    // printf("passed strcat \n");

    reply = redisCommand(c,"HMSET %d %s %s", ps->supl->supplier_id, number, ps->prod->product_code );
}



product *make_product(int pro_id, char *pro_code, int qua, int price ){
    product *pro = malloc(sizeof(product));
    pro->product_id = pro_id;
    pro->product_code = pro_code;
    pro->quatity = qua;
    pro->price = price;

    return pro;
    }
supplier *make_supplier( char *name, int supl_id, int phone){
    supplier *sup = malloc(sizeof(supplier));
    sup->name = name;
    sup->supplier_id = supl_id;
    sup->phone = phone;

    return sup;
}
productSupplier *make_productSuplier(product *pro,supplier *sup ){
    productSupplier *proSup = malloc(sizeof(productSupplier));
    proSup->prod = pro;
    proSup->supl = sup;

    return proSup;
}


void destory_product( product *pro){
    free(pro);
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
reply = redisCommand(c, "HMSET %s %s %d", "isGlass", "pruduct id", 12343);

product *pro1 = make_product(1234,"glass",43,2000);
add_product_to_redis(c, reply, pro1);

product *pro2 = make_product(432,"bok",20034,70200);
add_product_to_redis(c, reply, pro2);

product *pro3 = make_product(543312,"leksak",9900,3);
add_product_to_redis(c, reply, pro3);


supplier *sup1 = make_supplier("IKEA",123,0715160202);
add_supplier_to_redis(c,reply, sup1);

supplier *sup2 = make_supplier("GOGO",12345 ,5432);
add_supplier_to_redis(c,reply, sup2);

productSupplier *ikea1 = make_productSuplier(pro2,sup1);
productSupplier *ikea2 = make_productSuplier(pro3,sup1);
productSupplier *GOGO = make_productSuplier(pro1,sup2);

add_prodSupl_to_redis(c,reply, ikea1,"1");
add_prodSupl_to_redis(c,reply, ikea2,"2");
add_prodSupl_to_redis(c,reply, GOGO,"1");

freeReplyObject(reply);



redisFree(c);
}

