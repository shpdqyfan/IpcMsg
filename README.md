# IpcMsg
IpcMsg is an encapsulation of operation of socket communication. It's also an example to show how to layout the folder structure of lib in project. We can put #1 into our library path of project and put #2 into the path where would be exposed to outside. 

IpcMsg project                                                                                                                             
|-----IpcMsg                      #1 src path of IpcMsg lib                                                                               
|-----|-----CMakeLists.txt                                                                                                                 
|-----|-----src                                                                                                                           
|-----|-----include                                                                                                                       
|-----include                     #2 header files path of IpcMsg lib                                                                       
|-----|-----IpcMsg                                                                                                                         
|-----CMakeLists.txt                                                                                                                       
