# 42-CPP09

## ex02

### Ford-Johnson Algorithm

1.	Pair adjacent elements together and compare them. Swap them if they're out of order. Ignore any unpaired element (we call it a `straggler`).
2.	Repeat step '1' by creating pair of pairs, pair of pairs of pairs...

    a. In subsequent pairings, 2 elements will make up a 'unit' (an entity of a pair; each pair has two units), then 4, 8, ...

    b. When comparing units with more than 1 element, we compare the largest element of each unit _only_.

4. For each recursion level, create a `main` and `pend` chain. The `main` chain will consist of units that are larger within a pair while the `pend` chain will consist of units that are smaller. Once completed, move the first unit of the `pend` chain to the beginning of the `main` chain.

    a. We label units in a pair as `bₓ, aₓ` where `aₓ >= bₓ`.

    b. Therefore, after step '3', our `main` and `pend` chains should be as follows:
        
        main: b₁, a₁, a₂, a₃ ...
        pend: b₂, b₃, ...

5.	If a `straggler` exists, insert it at the end of the `pend` chain.
6.	Insert units in `pend` into `main` in an order determined by Jacobsthal numbers. Jacobsthal numbers ensure that the surface area for searching an appropriate index for binary insertion is maximized using the least number of comparisons (max num of comparisons for searching within 2<sup>n</sup> and 2<sup>n+1</sup> - 1 elements are the same, so we try to search within 2<sup>n+1</sup> - 1 elements as much as possible).

    a.	Jacobsthal sequence: 0, 1, 1, 3, 5, 11, 21, ... (https://en.wikipedia.org/wiki/Jacobsthal_number)

  	b.	Use '3' as the first current J<sub>num</sub>. This number tells us the surface area for searching (most of the time it's 2<sup>n+1</sup> - 1 but we have to count inserted units and offsets in later insertions).

    c.	The difference between the current J<sub>num</sub> and the previous J<sub>num</sub> tells us how many `pend` units we should insert and which unit to start inserting from (we start from `diff - 1` and we work to the front). Insert units into `main` using binary insertion.

    d.	If the unit inserts directly at the last search unit of the `main`, add an offset value to ensure the last unit to search until (i.e., the search area) doesn't get affected in subsequent insertions.

    e.	If there are sufficient numbers in `pend`, move on to the next J<sub>num</sub> and repeat the whole process.

8.	If `pend` still has units but the order of insertion cannot be determined using J<sub>num</sub>, insert using binary insertion with the search area determined by `aₓ` of the current `bₓ` unit.
		a.	E.g., if we're inserting `b₂`, the bound will be `a₂` since it's guaranteed that `a₂ >= b₂`.

Implementation detail: due to the fact that we store the iterators of the elements of the original container, we have to copy the new ordering into a new container before overwriting the original container.

### Container Comparison

#### Memory Layout

- Vectors store elements contiguously in memory which leads to faster access times for individual elements especially if memory is accessed sequentially.
 - Double-ended queues store multiple blocks of memory which aren't contiguous. This leads to frequent cache-misses which means slower access times.

#### Insertions/Deletions
- Vectors support fast insertions/deletions at the end but can be slow in the middle as shifting is required.
- Deques support fast insertions/deletions at both ends but can be slower in the middle than in a vector as entire blocks may have to be rearranged.

#### Conclusion
- The Ford-Johnson algorithm using vectors is likely to be faster than the one using deques. Faster random access iterators could be a small factor contributing to this discrepancy but the binary insertion probably slowed it down significantly (see `std::upperbound()` in the code and the subsequent insertion).

### Resources
- [Human explanation and step-by-step visualisation of the Ford-Johnson algorithm](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91)
- [Code Review Stack Exchange: Ford-Johnson merge-insertion sort](https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort)
- The Art of Computer Programming by Donald Knuth
