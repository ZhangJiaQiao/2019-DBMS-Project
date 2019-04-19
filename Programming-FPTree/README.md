

# 代码框架讲解
下面针对框架中的每一个主要对象以及其组成进行实现说明，规定相关细节。
## FPTree
这是整个键值存储系统的接口类，通过其调用InnerNode进而调用LeafNode进行键值对操作。一个FPTree就是一个键值对库，对应一个文件夹。其数据文件与PAllocator的管理文件存在在同一个文件夹下。**请自行注明数据的存储位置(NVM挂载的文件夹)，定义在utility.h中的DATA_DIR变量**

## Node
这是InnerNode和LeafNode的父类对象，其相关限制在子类对象一样适用。其有一些两种节点共有的属性，本身的方法大多是纯虚函数，由子对象自己实现。

## KeyNode
这个数据结构由一个代表键值和节点的索引组成，用于节点分裂时，将新生成的节点索引返回给上层节点插入记录。其用在插入操作和分裂操作中。

## InnerNode
管理方法和书本的B+tree基本一致。
### 节点元素细节
通过对节点的合并和分裂操作，保证每个节点的元素个数限制在以下范围(FPTree的根少于d)：  
key个数 : d <= m <= 2d </br>
node指针个数 : d + 1 <= m < = 2d + 1 </br>

记得保持节点元素有序，这样才可以使用二分查找findIndex。**键值的搜索规则是左闭右开原则**，与书本的一直，即Km <= search <Km+1，Km和Km+1所夹住的索引即为目标节点

### 键值对删除（困难）
#### 直接对应函数
bool InnerNode::remove(Key k, int index, InnerNode* parent, bool &ifDelete)
#### 函数参数说明
1. k：目标键值对的键
2. index：当前节点属于其父亲节点的第几个元素
3. parent：当前节点的父亲节点
4. ifDelete：当前节点为空则需要删除，返回给父亲节点是否删除的信息

index和parent都是方便节点删除元素后进行重分布或者合并操作，方便获得其兄弟节点。返回值为是否删除成功。

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
9. int InnerNode::findIndex()：二分查找

### 键值对插入（中等）
#### 直接对应函数
KeyNode* InnerNode::insert(Key k, Value v)
#### 函数参数说明
1. k：插入键值对的键
2. v：插入键值对的值

返回值为KeyNode，下层子节点分裂后生成新的节点，将节点索引以及代表键值返回给上层节点插入
#### 函数说明
这是InnerNode插入键值对的函数，不进行实际的键值对插入，通过递归调用其子节点插入，直至叶子结点进行实际的插入。对子节点分裂后返回的KeyNode值进行插入。

#### 细节
第一次插入或者只有一个叶子时，也只有一个中间节点，这时候需要特殊处理。形成两个叶子后插入正常进行。当节点元素多过限制时，进行节点分裂操作。
#### 调用的函数
1. KeyNode* InnerNode::split()：分裂满了的节点
2. int InnerNode::findIndex()：二分查找
3. void InnerNode::insertNotFull()：节点不满直接插入，保持元素有序
4. void FPTree::changeRoot(): 当根节点满时分裂，并产生新的根节点
### 键值对查询（简单）
#### 直接对应函数
Value InnerNode::find(Key k)
#### 函数说明
这是InnerNode的查询函数，不进行实际的查询。二分查找目标子节点，递归调用其对应子节点的查询函数，直至叶子节点进行实际的查询，返回查询得到的值。查询失败返回MAX_VALUE。

### 键值对修改（简单）
#### 直接对应函数
bool InnerNode::update(Key k, Value v)

#### 函数说明
这是InnerNode更新键值对的函数，递归调用至叶子节点进行实际的更新，返回值为是否更新成功。因为框架限制，不能执行论文里的先插入再删除策略实现更新，有想法的同学可以将返回值改成KeyNode*，在叶子节点的update里进行先插入在删除（测试代码不兼容，请另外实现一个函数，注明为额外工作）。

## LeafNode

### 节点元素细节
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
