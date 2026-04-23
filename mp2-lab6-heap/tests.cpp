#include"gtest.h"
#include"Heap.h"
#include<vector>
//#include "gtest.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Dheap, can_create)
{
    DHeap<int> heap;
}
TEST(Dheap, insert)
{
    DHeap<int> heap;    
    std::vector<int> vec = { 10,9,8,7,6,5 };
    heap.Insert(10);
    heap.Insert(9);
    heap.Insert(8);
    heap.Insert(7);
    heap.Insert(6);
    heap.Insert(5);
    for (int i = 0; i < 6; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }

}
TEST(Dheap, surfacing)
{
    DHeap<int> heap;
    std::vector<int> vec = { 20,9,10,7,6,5,8 };
    heap.Insert(10);
    heap.Insert(9);
    heap.Insert(8);
    heap.Insert(7);
    heap.Insert(6);
    heap.Insert(5);
    heap.Insert(20);
    for (int i = 0; i < 7; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, delete)
{
    DHeap<int> heap;
    std::vector<int> vec = { 10,9,5,7,6 };
    heap.Insert(10);
    heap.Insert(9);
    heap.Insert(8);
    heap.Insert(7);
    heap.Insert(6);
    heap.Insert(5);
    heap.Delete(2);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, dive)
{
    DHeap<int> heap;
    std::vector<int> vec = { 3,1,2 };
    heap.Insert(1);
    heap.Insert(2);
    heap.Insert(3);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, delete_root)
{
    DHeap<int> heap;
    std::vector<int> vec = { 2,1 };
    heap.Insert(1);
    heap.Insert(2);
    heap.Insert(3);
    heap.Delete(0);
    for (int i = 0; i < 2; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
    TEST(Dheap, heapify)
    {
        std::vector<int> vec = { 2,1,3,4 };
        std::vector<int> res = { 4,2,3,1};
        DHeap<int> heap;
        DHeap<int> new_heap = heap.heapify(vec, 2);
        for (int i = 0; i < 4; i++)
        {
            //std::cout << new_heap.Get_element(i) << std::endl;
            EXPECT_EQ(new_heap.Get_element(i), res[i]);
        }
    }
    TEST(Dheap, rehash)
    {
        DHeap<int> heap(2,2);
        std::vector<int> vec = { 2,1 };
        heap.Insert(1);
        heap.Insert(2);
        heap.Insert(3); 
        EXPECT_EQ(heap.Get_size(), 4);
    }