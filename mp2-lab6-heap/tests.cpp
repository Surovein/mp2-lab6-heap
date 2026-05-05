#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include"gtest.h"
#include"Heap.h"
#include<vector>
#include"Dijkstra's algorithm.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Dheap, can_create)
{
    DHeap<int> heap;
}
TEST(Dheap, insert_max)
{
    DHeap<int, std::greater<int>> heap;
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
TEST(Dheap, insert_min)
{
    DHeap<int> heap;
    std::vector<int> vec = { 5,6,7,8,9,10 };
    heap.Insert(5);
    heap.Insert(6);
    heap.Insert(7);
    heap.Insert(8);
    heap.Insert(9);
    heap.Insert(10);
    for (int i = 0; i < 6; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }

}
TEST(Dheap, surfacing_max)
{
    DHeap<int, std::greater<int>> heap;
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
TEST(Dheap, surfacing_min)
{
    DHeap<int> heap;
    std::vector<int> vec = {7,8,9,10};
    heap.Insert(10);
    heap.Insert(9);
    heap.Insert(8);
    heap.Insert(7);
    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, delete_max)
{
    DHeap<int, std::greater<int>> heap;
    std::vector<int> vec = { 10,9,5,7,6,4 };
    heap.Insert(10);
    heap.Insert(9);
    heap.Insert(8);
    heap.Insert(7);
    heap.Insert(6);
    heap.Insert(5);
    heap.Insert(4);
    heap.Delete(2);
    for (int i = 0; i < 6; i++)
    {
       // std::cout << heap.Get_element(i) << std::endl;
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, delete_min)
{
    DHeap<int> heap;
    std::vector<int> vec = { 4,7,6};
    heap.Insert(4);
    heap.Insert(5);
    heap.Insert(6);
    heap.Insert(7);
    heap.Delete(1);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, dive_max)
{
    DHeap<int, std::greater<int>> heap;
    std::vector<int> vec = { 3,1,2 };
    heap.Insert(1);
    heap.Insert(2);
    heap.Insert(3);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, dive_min)
{
    DHeap<int> heap;
    std::vector<int> vec = { 1,3,2 };
    heap.Insert(3);
    heap.Insert(1);
    heap.Insert(2);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(heap.Get_element(i), vec[i]);
    }
}
TEST(Dheap, delete_root_max)
{
    DHeap<int, std::greater<int>> heap;
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
    TEST(Dheap, heapify_max)
    {
        std::vector<int> vec = { 2,1,3,4 };
        std::vector<int> res = { 4,2,3,1};
        DHeap<int, std::greater<int>> heap;
        DHeap<int, std::greater<int>> new_heap = heap.heapify(vec, 2);
        for (int i = 0; i < 4; i++)
        {
            //std::cout << new_heap.Get_element(i) << std::endl;
            EXPECT_EQ(new_heap.Get_element(i), res[i]);
        }
    }
    TEST(Dheap, heapify_min)
    {
        std::vector<int> vec = { 2,1,3,4 };
        std::vector<int> res = { 1,2,3,4 };
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
    TEST(Dheap, max)
    {
        DHeap<int, std::greater<int>> heap;
       // std::vector<int> vec = { 2,1 };
        heap.Insert(1);
        heap.Insert(2);
        heap.Insert(3);
        EXPECT_EQ(heap.Getmax(), 3);
    }
    TEST(Dheap, min)
    {
        DHeap<int > heap;
        // std::vector<int> vec = { 2,1 };
        heap.Insert(3);
        heap.Insert(2);
        heap.Insert(1);
        EXPECT_EQ(heap.Getmax(), 1);
    }
    //TEST(Dijkstra, create)
    //{
    //    Dijkstra a();
    //}
    //TEST(Dijkstra, )
    //{
    //    int c = 4;
    //    int start = 0;
    //    int finish = 3;
    //    std::vector<std::vector<Dijkstra::edge>> matrix = 
    //    {
    //        { Dijkstra::edge(0, 0), Dijkstra::edge(1, 1), Dijkstra::edge(1, 2),Dijkstra::edge(0, 0) },
    //        { Dijkstra::edge(1, 1), Dijkstra::edge(0, 0), Dijkstra::edge(0, 0),Dijkstra::edge(1, 1) },
    //        { Dijkstra::edge(1, 2), Dijkstra::edge(0, 0), Dijkstra::edge(0, 0),Dijkstra::edge(1, 1) },
    //        {Dijkstra::edge(0, 0), Dijkstra::edge(1, 1), Dijkstra::edge(1, 1),Dijkstra::edge(0, 0) },
    //    };
    //    Dijkstra a(c,start,finish,matrix);
    //    EXPECT_EQ(a.Algorithm(), 2);
    //}