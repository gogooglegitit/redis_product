# redis_product
a small test of useing the redis server


uses the hiredis library to talk to the redis server. 

TODO: 
right now we need to just create some basic function for adding and other stuff into the redis server. 
if you like to get the code working on you computer you are welcome to try, it is a bit complicated but axel can help you
otherwise use make a function sketch (ass good as possible) and then we can get it working on axels computer. 


in the redis.c file I have outlined som basic functions and basic structur

the redis hashes seemed like the best alternative for storing datastructurs so use it. 

every products code is the key for its content and the rest of the field and values are the rest of the prod_struct,
to same for the supplier. the supplier name is the key for the hash-set. 

but since the supplier name is the key for the supplier we have to use the supplier_id for the productsupplier structure. to find which products a supplier

USEFULL LINKES:
https://www.tutorialspoint.com/redis/redis_hashes.htm
https://redis.io/commands/?group=hash

to install hiredis: 
https://github.com/redis/hiredis
