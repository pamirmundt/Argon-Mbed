#ifndef FLOAT32VAR_h
#define FLOAT32VAR_h

namespace argonSerial{
    class float32Var{
    public:
        float data;

        float32Var():
            data(0.0f)
        {
        }

        int serialize(unsigned char * outbuffer){
            int offset = 0;
            union {
                float real;
                uint32_t base;
            } u_data;
            u_data.real = this->data;
            *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
            *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
            *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
            *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
            offset += sizeof(this->data);
            return offset;
        }
        
        int deserialize(unsigned char * inbuffer)
        {
            int offset = 0;
            union {
                float real;
                uint32_t base;
            } u_data;
            u_data.base = 0;
            u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
            u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
            u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
            u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
            this->data = u_data.real;
            offset += sizeof(this->data);
            return offset;
        }
    };
}
#endif

