/*
 * nbt.c
 *
 *  Created on: Mar 25, 2016
 *      Author: root
 */

#include "nbt.h"
#include <stdlib.h>

void freeNBT(struct nbt_tag* nbt) {
	if (nbt->name != NULL) free(nbt->name);
	if (nbt->children != NULL) {
		for (size_t i = 0; i < nbt->children_count; i++) {
			freeNBT(nbt->children[i]);
			free(nbt->children[i]);
		}
		free(nbt->children);
	}
	if (nbt->id == NBT_TAG_BYTEARRAY) {
		free(nbt->data.nbt_bytearray.data);
	} else if (nbt->id == NBT_TAG_STRING) {
		free(nbt->data.nbt_string);
	} else if (nbt->id == NBT_TAG_INTARRAY) {
		free(nbt->data.nbt_intarray.ints);
	}
}
