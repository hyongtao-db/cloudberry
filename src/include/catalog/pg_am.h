/*-------------------------------------------------------------------------
 *
 * pg_am.h
 *	  definition of the "access method" system catalog (pg_am)
 *
 *
 * Portions Copyright (c) 1996-2021, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/catalog/pg_am.h
 *
 * NOTES
 *	  The Catalog.pm module reads this file and derives schema
 *	  information.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_AM_H
#define PG_AM_H

#include "catalog/genbki.h"
#include "catalog/pg_am_d.h"

/* GPDB: convenient macro for checking AO AMs */
#define IsAccessMethodAO(am_oid) \
	((am_oid) == AO_ROW_TABLE_AM_OID || (am_oid) == AO_COLUMN_TABLE_AM_OID)

/* ----------------
 *		pg_am definition.  cpp turns this into
 *		typedef struct FormData_pg_am
 * ----------------
 */
CATALOG(pg_am,2601,AccessMethodRelationId)
{
	Oid			oid;			/* oid */

	/* access method name */
	NameData	amname;

	/* handler function */
	regproc		amhandler BKI_LOOKUP(pg_proc);

	/* see AMTYPE_xxx constants below */
	char		amtype;
} FormData_pg_am;

/* GPDB added foreign key definitions for gpcheckcat. */
FOREIGN_KEY(amhandler REFERENCES pg_proc(oid));

/* ----------------
 *		Form_pg_am corresponds to a pointer to a tuple with
 *		the format of pg_am relation.
 * ----------------
 */
typedef FormData_pg_am *Form_pg_am;

DECLARE_UNIQUE_INDEX(pg_am_name_index, 2651, on pg_am using btree(amname name_ops));
#define AmNameIndexId  2651
DECLARE_UNIQUE_INDEX_PKEY(pg_am_oid_index, 2652, on pg_am using btree(oid oid_ops));
#define AmOidIndexId  2652

#ifdef EXPOSE_TO_CLIENT_CODE

/*
 * Allowed values for amtype
 */
#define AMTYPE_INDEX					'i' /* index access method */
#define AMTYPE_TABLE					't' /* table access method */

#endif							/* EXPOSE_TO_CLIENT_CODE */

#endif							/* PG_AM_H */
