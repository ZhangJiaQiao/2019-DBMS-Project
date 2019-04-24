#include <iostream>
#include <time.h>
#include"fptree/fptree.h"

using namespace std;

void testSplit() {
    FPTree* tree = new FPTree(4);

    for (int i = 1; i < 33; i++) {
        tree->insert(i, i * 10);
    }
    tree->printTree();
    delete tree;
}

void testInsert() {
    FPTree* tree = new FPTree(2);
    tree->insert(1, 100);
    LeafNode* leaf = (LeafNode*)tree->getRoot()->getChild(0);
    
    LeafNode* t_leaf = new LeafNode(leaf->getPPointer(), tree);
}

void testLeafRead() {
    std::ofstream out("../data/1", std::ios::out|std::ios::binary|ios::trunc);
    int bitNum = (2 * LEAF_DEGREE + 7) / 8;
    Byte* bitmap = new Byte[bitNum]();
    memset(bitmap, 0, bitNum);
    bitmap[0] = 0x80;
    PPointer p;
    p.fileId = 0;
    p.offset = 0;
    Byte* fp = new Byte[LEAF_DEGREE * 2]();
    memset(fp, 0, 2 * LEAF_DEGREE);
    fp[0] = 33;
    Key* keys = new Key[2 * LEAF_DEGREE]();
    Value* values = new Value[2 * LEAF_DEGREE]();
    memset(keys, 0, sizeof(Key) * 2 * LEAF_DEGREE);
    memset(values, 0, sizeof(Value) * 2 * LEAF_DEGREE);
    keys[0] = 1;
    values[0] = 100;
    out.write((char*)(bitmap), sizeof(Byte) * bitNum);
    out.write((char*)&(p), sizeof(PPointer));
    for (int i = 0; i < 2 * LEAF_DEGREE; i++) {
        out.write((char*)&(fp[i]), sizeof(Byte));
    }
    for (int i = 0; i < 2 * LEAF_DEGREE; i++) {
        out.write((char*)&(keys[i]), sizeof(Key));
        out.write((char*)&(values[i]), sizeof(Value));
    }
    out.close();
    out.clear();


    PPointer t_p;
    t_p.fileId = 1;
    t_p.offset = 0;

    LeafNode leaf(t_p, NULL);
    cout << "value : " << leaf.find(1) << endl;
    remove("../data/1");
}

void testBulkLoading() {
    FPTree* tree1 = new FPTree(1);
    for (int i = 1; i < LEAF_DEGREE * 2 * 4; i++) {
        tree1->insert(i, i * 100);
    }
    delete tree1;
    FPTree* tree2 = new FPTree(1);
    tree2->bulkLoading();
}

int main() {
    clock_t start, end;
    start = clock();
    FPTree *tree = new FPTree(32);
    tree->printTree();

    for (int i = 40000; i <= 50000; i++) {
        tree->insert(i, i* 10);
    }
    end = clock();
    double dur = end - start;
    cout << "Insert Used Time = " << (dur / CLOCKS_PER_SEC) << endl;

    delete tree;
    tree = NULL;
    PAllocator::getAllocator()->~PAllocator();

    FPTree *t_tree = new FPTree(32);
    start = clock();
    for (int i = 40000; i <= 50000; i++) {
        t_tree->find(i);
    }
    end = clock();
    double t_dur = end - start;
    cout << "Find Used Time = " << (t_dur / CLOCKS_PER_SEC) << endl;
}