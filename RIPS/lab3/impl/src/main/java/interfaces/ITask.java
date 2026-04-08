package interfaces;

public interface ITask<T> {
    T execute(int start, int end);
}