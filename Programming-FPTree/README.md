

# 代码框架讲解
下面针对框架中的每一个主要对象以及其组成进行实现说明，规定相关细节。
## FPTree
这是整个键值存储系统的接口类，通过其调用InnerNode进而调用LeafNode进行键值对操作。一个FPTree就是一个键值对库，对应一个文件夹。其数据文件与PAllocator的管理文件存在在同一个文件夹下。**请自行注明数据的存储位置(NVM挂载的文件夹)，定义在utility.h中的DATA_DIR变量**

## Node
这是InnerNode和LeafNode的父类对象，其相关限制在子类对象一样适用。其有一些两种节点共有的属性，本身的方法大多是纯虚函数，由子对象自己实现。

## InnerNode

### 节点元素个数限制
通过对节点的合并和分裂操作，保证每个节点的元素个数限制在以下范围(FPTree的根少于d)：  
key个数 : d <= m <= 2d </br>
node指针个数 : d + 1 <= m < = 2d + 1 </br>

### 键值对删除（困难）
#### 直接对应函数
void InnerNode::remove(Key k, int index, InnerNode* parent, bool &ifDelete)
#### 函数参数说明
1. k：目标键值对的键
2. index：当前节点属于其父亲节点的第几个元素
3. parent：当前节点的父亲节点
4. ifDelete：当前节点为空则需要删除，返回给父亲节点是否删除的信息

index和parent都是方便节点删除元素后进行重分布或者合并操作，方便获得其兄弟节点。

#### 函数说明
这是InnerNode删除键值对元素的函数，其不进行实际的键值对删除，通过递归调用其子节点删除，一直到叶子节点进行实际的删除。对子节点返回的信息进行处理，识别其下层调用的节点是否要被删除。删除子节点的时候，识别当前节点元素是否符合限制，不符合则进行重分布，重分布不行再合并。

#### 细节
当其子节点需要删除时，检查是否需要重分布和合并。合并的时候需要注意其父亲节点是否是根节点且其只有两个孩子，那么就合并这三者。注意的是如果同时有左右兄弟，左兄弟可以进行重分布，右兄弟可以合并，优先重分布。删除过程中一共有7种情况：
1. 子节点没有被删除，ifDelete返回给父亲节点
2. 子节点被删除，出现下面6六种情况：
   1. 当前节点元素足够，不需要进行重分布和合并
   2. 当前节点元素不够，与左兄弟重分布
   3. 当前节点元素不够，与右兄弟重分布
   4. 当前节点元素不够，与左兄弟合并
   5. 当前节点元素不够，与右兄弟合并
   6. 当前节点元素不否，父亲只有两个孩子(左或右)且父亲节点为根节点，合并这三者

#### 调用的函数
1. int InnerNode::findIndex：二分查找目标子节点。
2. void InnerNode::getBrother()：获得中间节点的左右兄弟节点。如果左右兄弟都存在，统一处理右兄弟。
3. void InnerNode::redistributeRight()：与右兄弟重分布
4. void InnerNode::redistributeLeft()：与左兄弟重分布
5. void InnerNode::mergeLeft()：与左兄弟合并
6. void InnerNode::mergeRight()：与右兄弟合并
7. void InnerNode::mergeParentLeft()：与父亲节点以及左兄弟合并
8. void InnerNode::mergeParentRight()：与父亲节点以及右兄弟合并

### 键值对插入

#### 直接对应函数

### 键值对查询

### 键值对修改

### 节点分裂

### 节点合并

### 节点删除

## LeafNode

### 节点元素个数限制
为了减少对NVM的写操作，叶子的元素个数只需控制小于2d即可，没有元素就删除叶子。所以没有叶子节点的合并操作。
键值对个数 : 0 < m < 2d </br>

### 键值对删除

### 键值对插入

### 键值对查询

### 键值对修改

### 叶子分裂

### 叶子合并
**没有叶子的合并操作**

### 叶子删除

## PAllocator
There are two file used for allocation management, p_allocator_catalog and free_list. Leaf group file is named by number counting from 1. 
