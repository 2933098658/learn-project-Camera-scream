


#设置一个依赖文件的存放地点
DEPEND_FILE := ./build_file/


# 自动创建存放依赖文件的目录
TARGET:= $(DEPEND_FILE)main

# 指定编译工具 gcc / arm-linux-gcc 
CC:= arm-linux-gcc


#创建依赖文件存放目录
$(shell mkdir -p $(DEPEND_FILE) )

# CSRCS 保存工程中 所有的.c文件的文件名列表 
# 1.c  2.c  3.c  ...
CSRCS:= $(wildcard *.c)

# OBJS 保存工程中 所有的.o文件的文件名列表 
# 1.o  2.o  3.o  ... 
OBJS:= $(addprefix $(DEPEND_FILE),$(patsubst %.c, %.o, $(CSRCS)))

# INC 保存工程中所有的头文件的搜索路径 ，-I 路径
#可以指定多个 -I 路径2  
INC:= -I ./

# LIBS 保存工程中所有的库的搜索路径，-L 库的路径  -l 库的名字
# 可以指定多个 -L 路径2  -lm   -pthread 
LIBS:= -L ./

$(DEPEND_FILE)%.o:%.c
	$(CC) -c $< $(INC) -o $@

$(TARGET):$(OBJS)
	$(CC) -g $^ $(LIBS) -o $@
	cp $@ /home/china/tftpboot/
# 将目标文件 拷贝到 tftp服务器的路径下，以便于网络传输




# 清除之前残留的中间文件： make clean
clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
