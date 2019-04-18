

# 代码框架讲解
下面针对框架中的每一个主要对象以及其组成进行实现说明，规定相关细节。
## FPTree

## Node
这是InnerNode和LeafNode的父类对象，其相关限制在子类对象一样适用。


## InnerNode

### 节点元素个数限制
通过对节点的合并和分裂操作，保证每个节点的元素个数限制在以下范围(FPTree的根少于d)：  
key个数 : d <= m <= 2d </br>
node指针个数 : d + 1 <= m < = 2d + 1 </br>

### 键值对删除

### 键值对插入

### 键值对查询

### 键值对修改

### 节点分裂

### 节点合并

### 节点删除

## LeafNode

### 节点元素个数限制
通过对节点的合并和分裂操作，保证每个节点的元素个数限制在以下范围(只有一个叶子时可以少于d)：  
键值对个数 : d <= m < 2d </br>

### 键值对删除

### 键值对插入

### 键值对查询

### 键值对修改

### 叶子分裂

### 叶子合并

### 叶子删除

## PAllocator
There are two file used for allocation management, p_allocator_catalog and free_list. Leaf group file is named by number counting from 1. 
