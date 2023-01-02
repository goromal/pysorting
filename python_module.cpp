#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sorting/Sorting.h>

namespace py = pybind11;

PYBIND11_MODULE(pysorting, m)
{
    m.doc() = "Python binding module for sorting.";

    py::enum_<sorting::ComparatorLeft>(m, "ComparatorLeft")
        .value("I", sorting::ComparatorLeft::I)
        .value("J", sorting::ComparatorLeft::J)
        .export_values();

    py::enum_<sorting::ComparatorResult>(m, "ComparatorResult")
        .value("NOT_COMPARED", sorting::ComparatorResult::NOT_COMPARED)
        .value("LEFT_LESS", sorting::ComparatorResult::LEFT_LESS)
        .value("LEFT_GREATER", sorting::ComparatorResult::LEFT_GREATER)
        .value("LEFT_EQUAL", sorting::ComparatorResult::LEFT_EQUAL)
        .export_values();

    py::class_<sorting::QuickSortState>(m, "QuickSortState")
        .def(py::init())
        .def_readwrite("sorted", &sorting::QuickSortState::sorted)
        .def_readwrite("n", &sorting::QuickSortState::n)
        .def_readwrite("arr", &sorting::QuickSortState::arr)
        .def_readwrite("stack", &sorting::QuickSortState::stack)
        .def_readwrite("top", &sorting::QuickSortState::top)
        .def_readwrite("p", &sorting::QuickSortState::p)
        .def_readwrite("i", &sorting::QuickSortState::i)
        .def_readwrite("j", &sorting::QuickSortState::j)
        .def_readwrite("l", &sorting::QuickSortState::l)
        .def_readwrite("c", &sorting::QuickSortState::c);

    m.def("validateState", &sorting::validateState, "Verify that the input state is formatted logically.");
    m.def("persistStateToDisk",
          &sorting::persistStateToDisk,
          "Persist the sorting state to disk. Reports success status.");
    m.def("sortStateFromDisk",
          &sorting::sortStateFromDisk,
          "Recover the sorting state from disk. Reports success status.");
    m.def("restfulRandomizedQuickSort",
          &sorting::restfulRandomizedQuickSort,
          "RESTful Randomized Quick Sort with a client-side comparator. The "
          "input state should contain a comparator output value (unless it's the "
          "first iteration: top = UINT32_MAX && c = 0) and the output state "
          "should contain updated comparator inputs (unless sorting is complete: "
          "top = UINT32_MAX). Reports success status.");
    m.def("restfulQuickSort",
          &sorting::restfulQuickSort,
          "RESTful Quick Sort with a client-side comparator. The "
          "input state should contain a comparator output value (unless it's the "
          "first iteration: top = UINT32_MAX && c = 0) and the output state "
          "should contain updated comparator inputs (unless sorting is complete: "
          "top = UINT32_MAX). Reports success status.");
}
