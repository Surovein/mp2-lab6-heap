#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include"gtest.h"
#include"Heap.h"
#include<vector>
#include"Dijkstra's algorithm.h"
#include <boost/version.hpp>
#include <boost/heap/binomial_heap.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/pairing_heap.hpp>
#include <boost/heap/skew_heap.hpp>
#include <boost/heap/d_ary_heap.hpp>
#include <chrono>

//int main() {
//    // Проверка версии
//    std::cout << "Boost version: "
//        << BOOST_VERSION / 100000 << "."
//        << (BOOST_VERSION / 100) % 1000 << "."
//        << BOOST_VERSION % 100 << std::endl;
//
//    // Проверка Boost.Heap
//    boost::heap::binomial_heap<int> heap;
//    heap.push(10);
//    heap.push(5);
//    heap.push(15);
//
//    std::cout << "Top element: " << heap.top() << std::endl;
//    heap.pop();
//    std::cout << "After pop, top: " << heap.top() << std::endl;
//
//    return 0;
//}
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
        EXPECT_EQ(heap.Get_data_size(), 4);
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
    TEST(Dheap, DecreaseKey)
    {
        DHeap<int, std::greater<int> > heap;
        std::vector<int> vec = { 100, 3 ,1 };
        int index1 = heap.Insert_ret(3);
        int index2 = heap.Insert_ret(2);
        int index3 =  heap.Insert_ret(1);
        heap.DecreaseKey(index2, 100);
        EXPECT_EQ(heap.element(index1), vec[1]);
        EXPECT_EQ(heap.element(index2), vec[0]);
        EXPECT_EQ(heap.element(index3), vec[2]);
    }

    TEST(Dijkstra, create)
    {
        Dijkstra<DHeapBoostWrapper<Node>> a(4);
    }


//#include <chrono>  // Библиотека для работы со временем
//
//    auto start = std::chrono::steady_clock::now();  // Запоминаем время ДО выполнения
//
//    // ВАШ КОД (то, что хотим измерить)
//    Dijkstra<DHeapBoostWrapper<Node>> d(1000);      // Создаём объект Дейкстры
//    auto res = d.Algorithm(0, graph);               // Запускаем алгоритм
//
//    auto end = std::chrono::steady_clock::now();    // Запоминаем время ПОСЛЕ выполнения
//
//    // Вычисляем разницу в миллисекундах
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    std::cout << "Время: " << ms << " ms" << std::endl;  // Выводим результат
















    TEST(Dijkstra, alg1)
    {
        int c = 4;
        int start_ = 0;
        std::vector<std::vector<Dijkstra<DHeapBoostWrapper<Node>>::edge>> matrix =
        {
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(1, 1), Dijkstra<DHeapBoostWrapper<Node>>::edge(2, 2) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(0, 1),Dijkstra<DHeapBoostWrapper<Node>>::edge(3, 1) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(0, 2),Dijkstra<DHeapBoostWrapper<Node>>::edge(3, 1) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(1, 1), Dijkstra<DHeapBoostWrapper<Node>>::edge(2, 1) }
        };
        Dijkstra<DHeapBoostWrapper<Node>> a(c);

        auto start = std::chrono::steady_clock::now();

        std::vector<Dijkstra<DHeapBoostWrapper<Node>>::dist> res = a.Algorithm(start_, matrix);
       
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;
        std::vector<int> ans = { 0,1,2,2 };
        for (int i = 0; i < ans.size(); i++)
        {
           // std::cout << res[i].distance << std::endl;
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }

    TEST(Dijkstra, alg2)
    {
        int c = 4;
        int start_ = 0;
        std::vector<std::vector<Dijkstra<DHeapBoostWrapper<Node>>::edge>> matrix =
        {
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(1, 1), Dijkstra<DHeapBoostWrapper<Node>>::edge(2, 2), Dijkstra<DHeapBoostWrapper<Node>>::edge(3, 5) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(0, 1),Dijkstra<DHeapBoostWrapper<Node>>::edge(3, 1) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(0, 2),Dijkstra<DHeapBoostWrapper<Node>>::edge(3, 1) },
            { Dijkstra<DHeapBoostWrapper<Node>>::edge(1, 1), Dijkstra<DHeapBoostWrapper<Node>>::edge(2, 1), Dijkstra<DHeapBoostWrapper<Node>>::edge(0, 5) }
        };
        Dijkstra<DHeapBoostWrapper<Node>> a(c);

        auto start = std::chrono::steady_clock::now();


        std::vector<Dijkstra<DHeapBoostWrapper<Node>>::dist> res = a.Algorithm(start_, matrix);


        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;

        std::vector<int> ans = { 0,1,2,2 };
        for (int i = 0; i < ans.size(); i++)
        {
           // std::cout << res[i].distance << std::endl;
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }
    TEST(Dijkstra, pairing_heap)
    {
        // Правильная настройка pairing_heap
        using PairingHeap = boost::heap::pairing_heap<Node,
            boost::heap::mutable_<true>,           // ? обязательно для update
            boost::heap::compare<std::greater<Node>>>;

        using DijkstraType = Dijkstra<PairingHeap>;

        int c = 4;
        int start_ = 0;

        std::vector<std::vector<DijkstraType::edge>> matrix =
        {
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 2) },
            { DijkstraType::edge(0, 1), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(0, 2), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 1) }
        };

        DijkstraType a(c);

        auto start = std::chrono::steady_clock::now();

        auto res = a.Algorithm(start_, matrix);

        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;



        std::vector<int> ans = { 0, 1, 2, 2 };
        for (int i = 0; i < ans.size(); i++)
        {
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }

    TEST(Dijkstra, fibonacci_heap)
    {
        // Настройка fibonacci_heap как mutable
        using FibHeap = boost::heap::fibonacci_heap<Node,
            boost::heap::mutable_<true>,           // ? обязательно для update
            boost::heap::compare<std::greater<Node>>>;

        using DijkstraType = Dijkstra<FibHeap>;

        int c = 4;
        int start_ = 0;

        std::vector<std::vector<DijkstraType::edge>> matrix =
        {
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 2) },
            { DijkstraType::edge(0, 1), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(0, 2), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 1) }
        };

        DijkstraType a(c);


        auto start = std::chrono::steady_clock::now();


        auto res = a.Algorithm(start_, matrix);

        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;



        std::vector<int> ans = { 0, 1, 2, 2 };
        for (int i = 0; i < ans.size(); i++)
        {
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }
    TEST(Dijkstra, skew_heap_fixed)
    {
        using SkewHeap = boost::heap::skew_heap<Node,
            boost::heap::mutable_<true>,
            boost::heap::compare<std::greater<Node>>>;

        using DijkstraType = Dijkstra<SkewHeap>;

        int c = 4;
        int start_ = 0;

        std::vector<std::vector<DijkstraType::edge>> matrix =
        {
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 2) },
            { DijkstraType::edge(0, 1), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(0, 2), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 1) }
        };

        DijkstraType a(c);


        auto start = std::chrono::steady_clock::now();


        auto res = a.Algorithm(start_, matrix);


        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;



        std::vector<int> ans = { 0, 1, 2, 2 };
        for (int i = 0; i < ans.size(); i++)
        {
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }
    TEST(Dijkstra, d_ary_heap)
    {
        // Настройка d_ary_heap
        using DAryHeap = boost::heap::d_ary_heap<Node,
            boost::heap::arity<4>,                    // количество детей (4)
            boost::heap::mutable_<true>,              // нужно для update()
            boost::heap::compare<std::greater<Node>>>; // min-heap

        using DijkstraType = Dijkstra<DAryHeap>;

        int c = 4;
        int start_ = 0;

        std::vector<std::vector<DijkstraType::edge>> matrix =
        {
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 2) },
            { DijkstraType::edge(0, 1), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(0, 2), DijkstraType::edge(3, 1) },
            { DijkstraType::edge(1, 1), DijkstraType::edge(2, 1) }
        };

        DijkstraType a(c);

        auto start = std::chrono::steady_clock::now();


        auto res = a.Algorithm(start_, matrix);

        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "time: " << ms << " microseconds" << std::endl;

        std::vector<int> ans = { 0, 1, 2, 2 };
        for (int i = 0; i < ans.size(); i++)
        {
            EXPECT_EQ(res[i].distance, ans[i]);
        }
    }