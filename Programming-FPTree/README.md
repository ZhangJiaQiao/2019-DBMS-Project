# Node
key : d <= m <= 2d </br>
node : d + 1 <= m < = 2d + 1 </br>

# Data Structure Introduction
FPTree is like B+tree. The B+tree management is based on the B+tree in the book "Database Management Systems, 3'rd Edition".

## Class InnerNode

### Delete -- bool remove(Key k)
The Delete progress just simply remove the target KV, without rearranging the Node and merging. -- TODO

### Split -- void split()
Put the [0, d] entry to the old node, and the [d+1, 2*d] to the new child node. After the split, insert the new entry.

## Class LeafNode

# PAllocator
There are two file used for allocation management, p_allocator_catalog and free_list. Leaf group file is named by number counting from 1. 

# Attention
