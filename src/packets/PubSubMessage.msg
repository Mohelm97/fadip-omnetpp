import inet.common.packet.chunk.Chunk;
enum PubSubMessageType
{
    Subscription = 0;
    Publication = 1;
};
class PubSubMessage extends inet::FieldsChunk {
    chunkLength = inet::B(6);
    uint8_t hopCount = 0;
    uint32_t nonce;
    PubSubMessageType type;
    string topic;
    string nodeName;
}
