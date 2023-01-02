from wsgiref import validate
import pytest
from pysorting import (
    ComparatorLeft,
    ComparatorResult,
    QuickSortState,
    validateState,
    persistStateToDisk,
    sortStateFromDisk,
    restfulQuickSort,
)

UINT32_MAX = 0xffffffff

class TestSorting:
    def test_persistence(self):
        state = QuickSortState()
        assert not validateState(state)
        assert not persistStateToDisk("sort_state.log", state)
        state.n = 2
        state.arr = [0, 1]
        state.stack = [2, 3]
        state.top = 0
        state.p = 8
        state.i = 0
        state.j = 1
        state.l = int(ComparatorLeft.I)
        state.c = int(ComparatorResult.LEFT_LESS)
        assert persistStateToDisk("sort_state.log", state)
        assert not sortStateFromDisk("fake_log.log")[0]
        read_success, state2 = sortStateFromDisk("sort_state.log")
        assert read_success
        assert state.n == state2.n
        assert state.arr[0] == state2.arr[0]
        assert state.arr[1] == state2.arr[1]
        assert state.stack[0] == state2.stack[0]
        assert state.stack[1] == state2.stack[1]
        assert state.top == state2.top
        assert state.p == state2.p
        assert state.i == state2.i
        assert state.j == state2.j
        assert state.l == state2.l
        assert state.c == state2.c
    
    def test_incremental_sorting_short(self):
        values = {0: 4.8, 1: 10.0, 2: 1.0, 3: 2.5, 4: 5.0}
        state = QuickSortState()
        state.n = 5
        state.arr = [i for i in values.keys()]
        state.stack = [0 for i in range(state.n)]
        assert validateState(state)

        def updateComparator(a, b):
            if a < b:
                return int(ComparatorResult.LEFT_LESS)
            elif a > b:
                return int(ComparatorResult.LEFT_GREATER)
            else:
                return int(ComparatorResult.LEFT_EQUAL)
        
        iter = 0
        maxIters = 50
        while not (state.top == UINT32_MAX and state.c != 0) and iter < maxIters:
            iter_success, state_out = restfulQuickSort(state)
            assert iter_success
            state = state_out
            if state.l == int(ComparatorLeft.I):
                state.c = updateComparator(values[state.arr[state.i]], values[state.arr[state.p]])
            elif state.l == int(ComparatorLeft.J):
                state.c = updateComparator(values[state.arr[state.j]], values[state.arr[state.p]])
            iter += 1
        
        assert state.arr[0] == 2
        assert state.arr[1] == 3
        assert state.arr[2] == 0
        assert state.arr[3] == 4
        assert state.arr[4] == 1
