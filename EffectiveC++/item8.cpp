
class DBConnection
{
public:
    static DBConnection create() {}
    void close() {} // close connection; throw an exception if closing fails
};

class DBConn
{
public:
    void close()
    {
        db.close(); // new function for client use
        closed = true;
    }

    ~DBConn()
    {
        if (!closed)
        {
            try
            {
                db.close();
            }
            catch (...)
            {
                // std::abort() // terminate program
                // swallow the exceptions
            }
        }
    }

private:
    DBConnection db;
    bool closed;
};