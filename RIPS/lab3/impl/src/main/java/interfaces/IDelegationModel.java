package interfaces;

import java.util.List;

public interface IDelegationModel {
    <T> List<T> solve(ITask<T> task, int rangeStart, int rangeEnd, int threadCount, int subTaskCount);
}