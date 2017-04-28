# NAND OPERATE

### 1.random data output



  * chip_select
  * send a cmd 00h
  * send col addr
  * send row addr
  * send cmd 30h
  *  check busy
  * dout 0 -> N  
  * send cmd 05h
  * send col addr
  * send smd e0h
  * Dout 0 -> M   
