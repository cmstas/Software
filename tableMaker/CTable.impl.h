// classes for implementing CTable::setTable()

class CTableRowAppender
{
    public:
        CTableRowAppender(CTable& table)
            : m_table(table)
            , m_row(0)
        {}

        // N = 1
        template <typename T0>
        CTableRowAppender& operator() (const std::string& row_name, const T0& v1)
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v1, m_row, 0);
            m_row++;
            return *this;
        }


        // N = 2
        template <typename T0, typename T1>
        CTableRowAppender& operator() (const std::string& row_name, const T0& v0, const T1& v1)
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v1, m_row, 0);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_row++;
            return *this;
        }

        // N = 3
        template <typename T0, typename T1, typename T2>
        CTableRowAppender& operator() (const std::string& row_name, const T0& v0, const T1& v1, const T2& v2)
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_row++;
            return *this;
        }

        // N = 4
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_row++;
            return *this;
        }

        // N = 5
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_row++;
            return *this;
        }

        // N = 6
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_row++;
            return *this;
        }

        // N = 7
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_row++;
            return *this;
        }

        // N = 8
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_row++;
            return *this;
        }

        // N = 9
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7,
            typename T8
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7,
            const T8& v8
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_table.setCell(v8, m_row, 8);
            m_row++;
            return *this;
        }

        // N = 10 
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7,
            typename T8,
            typename T9
        >
        CTableRowAppender& operator() 
        (
            const std::string& row_name, 
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7,
            const T8& v8,
            const T9& v9
        )
        {
            m_table.setRowLabel(row_name, m_row);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_table.setCell(v8, m_row, 8);
            m_table.setCell(v9, m_row, 9);
            m_row++;
            return *this;
        }

    private:
        CTable& m_table;
        size_t m_row;
};


class CTableColumnLabeler
{
    public:
        CTableColumnLabeler(CTable& table) 
            : m_table(table) 
        {}

        // N = 1
        CTableRowAppender operator() (const std::string& c0)
        {
            m_table.setColLabel(c0, 0);
            return CTableRowAppender(m_table);
        }

        // N = 2
        CTableRowAppender operator() (const std::string& c0, const std::string& c1)
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            return CTableRowAppender(m_table);
        }

        // N = 3
        CTableRowAppender operator() (const std::string& c0, const std::string& c1, const std::string& c2)
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            return CTableRowAppender(m_table);
        }

        // N = 4
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2, 
            const std::string& c3
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            return CTableRowAppender(m_table);
        }

        // N = 5
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2,
            const std::string& c3, 
            const std::string& c4
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            return CTableRowAppender(m_table);
        }

        // N = 6
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2, 
            const std::string& c3, 
            const std::string& c4, 
            const std::string& c5
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            m_table.setColLabel(c5, 5);
            return CTableRowAppender(m_table);
        }

        // N = 7
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2,
            const std::string& c3, 
            const std::string& c4, 
            const std::string& c5,
            const std::string& c6
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            m_table.setColLabel(c5, 5);
            m_table.setColLabel(c6, 6);
            return CTableRowAppender(m_table);
        }

        // N = 8
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2,
            const std::string& c3, 
            const std::string& c4, 
            const std::string& c5,
            const std::string& c6, 
            const std::string& c7
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            m_table.setColLabel(c5, 5);
            m_table.setColLabel(c6, 6);
            m_table.setColLabel(c7, 7);
            return CTableRowAppender(m_table);
        }

        // N = 9
        CTableRowAppender operator() 
        (
            const std::string& c0, 
            const std::string& c1, 
            const std::string& c2,
            const std::string& c3, 
            const std::string& c4, 
            const std::string& c5,
            const std::string& c6, 
            const std::string& c7,
            const std::string& c8
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            m_table.setColLabel(c5, 5);
            m_table.setColLabel(c6, 6);
            m_table.setColLabel(c7, 7);
            m_table.setColLabel(c8, 8);
            return CTableRowAppender(m_table);
        }

        // N = 10 
        CTableRowAppender operator() 
        (
             const std::string& c0, 
             const std::string& c1, 
             const std::string& c2,
             const std::string& c3, 
             const std::string& c4, 
             const std::string& c5,
             const std::string& c6, 
             const std::string& c7,
             const std::string& c8,
             const std::string& c9
        )
        {
            m_table.setColLabel(c0, 0);
            m_table.setColLabel(c1, 1);
            m_table.setColLabel(c2, 2);
            m_table.setColLabel(c3, 3);
            m_table.setColLabel(c4, 4);
            m_table.setColLabel(c5, 5);
            m_table.setColLabel(c6, 6);
            m_table.setColLabel(c7, 7);
            m_table.setColLabel(c8, 8);
            m_table.setColLabel(c9, 9);
            return CTableRowAppender(m_table);
        }

    private:
        CTable& m_table;
};


// class for implementing CTable::setCells()
class CTableCellSetter
{
    public:

        CTableCellSetter(CTable& table) 
            : m_table(table) 
            , m_row(0)
        {}
        
        // N = 1
        template <typename T0>
        CTableCellSetter& operator() (const T0& v1)
        {
            m_table.setCell(v1, m_row, 0);
            m_row++;
            return *this;
        }
        
        // N = 2
        template <typename T0, typename T1>
        CTableCellSetter& operator() (const T0& v0, const T1& v1)
        {
            m_table.setCell(v1, m_row, 0);
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_row++;
            return *this;
        }
        
        // N = 3
        template <typename T0, typename T1, typename T2>
        CTableCellSetter& operator() (const T0& v0, const T1& v1, const T2& v2)
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_row++;
            return *this;
        }
        
        // N = 4
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_row++;
            return *this;
        }
        
        // N = 5
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_row++;
            return *this;
        }
        
        // N = 6
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_row++;
            return *this;
        }
        
        // N = 7
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_row++;
            return *this;
        }
        
        // N = 8
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_row++;
            return *this;
        }
        
        // N = 9
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7,
            typename T8
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7,
            const T8& v8
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_table.setCell(v8, m_row, 8);
            m_row++;
            return *this;
        }
        
        // N = 10 
        template 
        <
            typename T0, 
            typename T1, 
            typename T2, 
            typename T3,
            typename T4,
            typename T5,
            typename T6,
            typename T7,
            typename T8,
            typename T9
        >
        CTableCellSetter& operator() 
        (
            const T0& v0, 
            const T1& v1, 
            const T2& v2, 
            const T3& v3,
            const T4& v4,
            const T5& v5,
            const T6& v6,
            const T7& v7,
            const T8& v8,
            const T9& v9
        )
        {
            m_table.setCell(v0, m_row, 0);
            m_table.setCell(v1, m_row, 1);
            m_table.setCell(v2, m_row, 2);
            m_table.setCell(v3, m_row, 3);
            m_table.setCell(v4, m_row, 4);
            m_table.setCell(v5, m_row, 5);
            m_table.setCell(v6, m_row, 6);
            m_table.setCell(v7, m_row, 7);
            m_table.setCell(v8, m_row, 8);
            m_table.setCell(v9, m_row, 9);
            m_row++;
            return *this;
        }

    private:
        CTable& m_table;
        size_t m_row;
};
