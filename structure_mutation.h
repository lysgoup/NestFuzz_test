#include "afl-fuzz.h"
#include <stdbool.h>

cJSON* parse_json(const u8* format_file);
Chunk *parse_struture_file(u8 *path);
Track* parse_constraint_file(u8* path, u8 *in_buf);
void delete_block(Chunk* head, HashMap map, uint32_t delete_from,
                  uint32_t delete_len);
cJSON* tree_to_json(Chunk* chunk_head);
Chunk *json_to_tree(cJSON* json_head);
cJSON *track_to_json(Track *track);
void free_tree(Chunk *tree, Boolean recurse);
int32_t get_json_start(const cJSON *chunk);

int32_t get_json_end(const cJSON *chunk);

u8 *get_json_type(const cJSON *chunk);

Chunk *get_tree(cJSON *cjson_head);

u32 htoi(u8 s[]);

uint8_t *itoh(uint32_t num);

uint8_t *candidate_reverse(char *str);

uint8_t *parse_candidate(uint8_t *str, u32 *len);

cJSON *tree_to_json(Chunk *chunk_head);

cJSON *track_to_json(Track *track);

void tree_add_map(Chunk *head, HashMap map);

void free_tree(Chunk *head, Boolean recurse);

void free_enum(Enum *node);

void free_track(Track *track);

void number_add(u8 *buf, u32 start, u32 len, u32 num);

void number_subtract(u8 *buf, u32 start, u32 len, u32 num);

void number_set_interesting(u8 *buf, u32 start, u32 len, u32 index);

Chunk *get_random_chunk(Chunk *head);

Enum *get_random_enum(Enum *head);


Length *get_random_length(Length *head);

Offset *get_random_offset(Offset *head);

Constraint *get_random_constraint(Constraint *head);

cJSON *get_json(const u8 *path);

cJSON *get_structure_json(const u8 *path, const u8 *suffix);
cJSON *get_structure_json_for_reusing(const u8 *path, const u8 *suffix);

Chunk *json_to_tree(cJSON *cjson_head);
Boolean is_inferred(u8 *path);
Chunk *parse_struture_file(u8 *path);

Track *parse_constraint_file(u8 *path, u8 *in_buf);

Boolean chunk_overleap(Chunk *chunk1, Chunk *chunk2);

u8 *copy_and_insert(u8 *buf, u32 *len, u32 insert_at, u32 copy_start,
                    u32 copy_len);

u8 *insert_chunk(u8 *buf, u32 *len, HashMap map, u8 *insert_id, u8 *copy_id,
                 Boolean after);

u8 *delete_data(u8 *buf, u32 *len, u32 delete_start, u32 delete_len);


u8 *delete_chunk(u8 *buf, u32 *len, HashMap map, u8 *id);

void get_exchange_chunks(uint32_t chunk_num, uint8_t **all_chunks, HashMap map,
                         Chunk **chunks);

uint8_t *exchange_chunk(uint8_t *buf, uint32_t len, Chunk *chunk_left,
                        Chunk *chunk_right);

void struct_havoc_stage(char **argv, u8 *buf, u32 len, Chunk *tree,
                        Track *track);

void struct_describing_stage(char **argv, u8 *buf, u32 len, Chunk *tree,
                        Track *track);
                        
void constraint_aware_stage(char **argv, u8 *buf, u32 len, Chunk *tree,
                            Track *track);

void reusing_stage(char **argv, u8 *buf, u32 len, Chunk *tree,
                            Track *track);

/*For Reusing*/
#ifndef VALUE_SET_H
#define VALUE_SET_H
typedef struct UniqueValue {
  u8 *data;       // 값 (바이트 배열)
  u32 length;     // 값의 길이
  struct UniqueValue *next;
} UniqueValue;

typedef struct UniqueSet {
  UniqueValue *head;
  unsigned int count;
  void (*insert)(struct UniqueSet *, u8 *data, u32 length);
  bool (*contains)(struct UniqueSet *, u8 *data, u32 length);
} UniqueSet;

UniqueSet *enum_value_set;
UniqueSet *length_value_set;
UniqueSet *offset_value_set;
#endif

bool contains(UniqueSet *set, u8 *data, u32 length);
void insert(UniqueSet *set, u8 *data, u32 length);
void init_value_sets();

/*All Mutators*/
u8* insert_chunk_mutator(u8 *buf, u32 *len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* delete_chunk_mutator(u8 *buf, u32 *len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* exchange_chunk_mutator(u8 *buf, u32 *len, HashMap map, u8 **all_chunks, u32 chunk_num);

u8* enum_mutator(u8 *buf, u32 len, Enum *enum_field, u32 candi_index);

u8* increase_len_mutator(u8* buf, u32 len, Length *len_field, u32 num);
u8* decrease_len_mutator(u8* buf, u32 len, Length *len_field, u32 num);
u8* set_len_mutator(u8* buf, u32 len, Length *len_field, u32 interest_num);
u8* insert_len_payload_mutator(u8* buf, u32 *len, Length *len_field);
u8* delete_len_payload_mutator(u8* buf, u32 *len, Length *len_field);

u8* increase_offset_mutator(u8* buf, u32 len, Offset *offset_field, u32 num);
u8* decrease_offset_mutator(u8* buf, u32 len, Offset *offset_field, u32 num);
u8* set_offset_mutator(u8* buf, u32 len, Offset *offset_field, u32 interest_num);
u8* insert_offset_payload_mutator(u8* buf, u32 *len, Offset *offset_field);
u8* delete_offset_payload_mutator(u8* buf, u32 *len, Offset *offset_field);

u8* enum_insert_mutator(u8* buf, u32 *len, Enum *enum_field, HashMap map);
u8* enum_delete_mutator(u8* buf, u32 *len, Enum *enum_field, HashMap map);
u8* enum_exchange_mutator(u8* buf, u32 *len, Enum *enum_field, HashMap map);
u8* multiple_enum_mutator(u8* buf, u32 *len, Enum *enum_field, HashMap map, Track *track);
u8* high_order_structure_mutator(u8* buf, u32 *len, HashMap map, Chunk *tree);

u8* flip_bit_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* set_byte_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* set_word_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* set_dword_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* sub_byte_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* add_byte_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* sub_word_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* add_word_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* sub_dword_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* add_dword_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* random_set_byte_mutator(u8* buf, u32 len, HashMap map, u8 **all_chunks, u32 chunk_num);
u8* overwrite_with_enum_mutator(u8* buf, u32 *len, Enum *enum_field, u8 **all_chunks, u32 chunk_num);
u8* insert_with_enum_mutator(u8* buf, u32 *len, Enum *enum_field, u8 **all_chunks, u32 chunk_num);