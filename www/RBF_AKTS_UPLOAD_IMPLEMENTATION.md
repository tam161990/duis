# RBF Akts Upload Implementation

## Overview
This document describes the implementation of the RBF Akts Excel upload functionality, which allows administrators to import RBF acts data from Excel files into the `rbf_akti` table.

## Features Implemented

### 1. New Menu Item
- **Location**: Options submenu (after INFLATION)
- **Text**: "Upload RBF akti" (Latvian: "Upload RBF akti")
- **Form**: `f.adm.s.8`
- **Access**: Admin only

### 2. File Upload Form (`f.adm.s.8`)
- Excel file upload field (accepts .xls and .xlsx)
- File validation
- Bulk import processing
- Duplicate prevention (based on `FAKT_NUM_POSTFIX`)
- **File storage**: Uploaded Excel files are saved to `rbf_act_files` folder
- **File metadata**: File information is stored in `rbf_akta_files` table
- Success/error/skip statistics display

### 3. Excel File Structure
The Excel file must have the following columns in order:

| Column | Excel Header | Database Column | Required | Data Type | Max Length | Description |
|--------|-------------|-----------------|----------|-----------|------------|-------------|
| A | Darbuzņēmēja kods | FAKT_KWOI_KODS | Yes | VARCHAR | 11 | Employee/contractor code |
| B | VV numurs | FAKT_VV_NUMBER | Yes | VARCHAR | 20 | General agreement number |
| C | RBF nodaļa | FAKT_RBTR_KODS | Yes | VARCHAR | 10 | RBF department/territory code |
| D | Autors | FAKT_RLTT_TEXT | Yes | VARCHAR | 200 | Author name |
| E | Akta veids | FAKT_KAKV_KODS | Yes | CHAR | 3 | Act type code (e.g., "50", "100") |
| F | Pasūtījuma ID | FAKT_NUM_POSTFIX | Yes | VARCHAR | 20 | **Unique** order ID |
| G | Darba nosaukums | FAKT_WORK_TITLE | Yes | VARCHAR | 500 | Work title for printouts |
| H | Piezīmes | FAKT_PIEZIMES | No | VARCHAR | 150 | Additional notes (optional) |

**Important Notes:**
- First row (header) is skipped during import
- Records with existing `FAKT_NUM_POSTFIX` will NOT be imported again
- Empty rows are automatically skipped
- All required fields must be filled

### 4. Database Tables

#### `rbf_akti` Table
```sql
CREATE TABLE `rbf_akti` (
    `FAKT_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `FAKT_KWOI_KODS` VARCHAR(11) NOT NULL,        -- Employee code
    `FAKT_VV_NUMBER` VARCHAR(20) NOT NULL,         -- VV number
    `FAKT_RBTR_KODS` VARCHAR(10) NOT NULL,         -- Department code
    `FAKT_RLTT_TEXT` VARCHAR(200) NOT NULL,        -- Author
    `FAKT_KAKV_KODS` CHAR(3) NOT NULL,             -- Act type code
    `FAKT_NUM_POSTFIX` VARCHAR(20) NOT NULL,       -- Order ID (UNIQUE)
    `FAKT_WORK_TITLE` VARCHAR(500) NOT NULL,       -- Work title
    `FAKT_PIEZIMES` VARCHAR(150) NULL,             -- Notes
    PRIMARY KEY (`FAKT_ID`),
    UNIQUE INDEX `U_FAKT_NUM_POSTFIX` (`FAKT_NUM_POSTFIX`)
)
```

#### `rbf_akta_files` Table
```sql
CREATE TABLE `rbf_akta_files` (
    `FFLS_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `FFLS_NAME_ORIGINAL` VARCHAR(200) NOT NULL,   -- Original filename
    `FFLS_NAME_GENERATED` VARCHAR(200) NOT NULL,  -- System generated filename
    `FFLS_UPLOADED_DATE` DATETIME NOT NULL,       -- Upload timestamp
    `FFLS_PROCESSED_DATE` DATETIME NULL,          -- Processing date
    `FFLS_PROCESSED` CHAR(1) NOT NULL DEFAULT 0,  -- Processing status
    PRIMARY KEY (`FFLS_ID`)
)
```

## File Storage

When data is successfully imported:
1. **Excel file** is saved to `rbf_act_files/` folder with a unique generated name
2. **File metadata** is stored in `rbf_akta_files` table:
   - Original filename (as uploaded by user)
   - Generated filename (timestamp + unique ID + extension)
   - Upload timestamp
   - Processing status (initially set to '0')

**Generated filename format**: `YYYY-MM-DD_HH-ii-ss_[uniqueid].[ext]`
**Example**: `2024-12-19_15-30-45_657b3c4f5a123.xlsx`

## Files Modified/Created

### Created Files:
1. **`forms/f.adm.s.8.inc`** - Controller for RBF Akts upload form
2. **`forms/f.adm.s.8.tpl`** - Template for RBF Akts upload form

### Modified Files:
1. **`config/main.conf.php`** - Added constant:
   - `RBF_ACT_FILES_STORE_PATH` - Path to store uploaded Excel files
2. **`forms/f.inf.s.1.inc`** - Added `$rbfExportLink` for menu
3. **`forms/f.inf.s.1.tpl`** - Added RBF_EXPORT menu item after INFLATION
4. **`libs/dbProc/dbProc.class`** - Added three new functions:
   - `getRbfAktByPostfix($numPostfix)` - Check if record exists
   - `saveRbfAkt(...)` - Save imported record to database
   - `saveRbfAktFile($originalName, $generatedName)` - Save file metadata
5. **`sql/DUIS-549.sql`** - Added:
   - Text translations for menu and messages
   - `rbf_akti` table creation
   - `rbf_akta_files` table creation
   - Requirements documentation text
   - Form field labels

### Created Directories:
1. **`rbf_act_files/`** - Storage folder for uploaded Excel files

## Text Translations Added

The following text codes were added to `FMK_MESSAGES`:

| Code | Latvian Text | Usage |
|------|-------------|-------|
| RBF_EXPORT | Upload RBF akti | Menu item text |
| RBF_AKTS_FILE | Excel fails | File upload field label |
| RBF_IMPORT_SUCCESS | Veiksmīgi importēti ieraksti: | Success message |
| RBF_IMPORT_SKIPPED | Izlaisti jau eksistējoši ieraksti: | Skip message |
| RBF_IMPORT_ERRORS | Kļūdas importējot: | Error message |
| ERROR_INVALID_FILE_TYPE | Nederīgs faila tips! Atļautie tipi: .xls, .xlsx | File type validation error |
| ERROR_FILE_UPLOAD | Kļūda augšupielādējot failu! | Upload error |
| ERROR_PROCESSING_FILE | Kļūda apstrādājot failu | Processing error |
| ERROR_SAVING_FILE | Kļūda saglabājot failu! | File save error |
| ERROR_SAVING_FILE_INFO | Kļūda saglabājot faila informāciju! | File metadata save error |
| REQUIREMENTS_RBF_AKTS | [HTML table with requirements] | Form instructions |

## Import Logic

### Processing Flow:
1. **File Upload**: User selects Excel file (.xls or .xlsx)
2. **Validation**: System validates file extension
3. **Excel Reading**: PHPExcel library reads the file
4. **Row Processing**: For each row (starting from row 2):
   - Read all 8 columns (A-H)
   - Skip if row is empty
   - Validate required fields
   - Check if `FAKT_NUM_POSTFIX` already exists
   - If exists: skip and increment skip counter
   - If new: insert into `rbf_akti` table
5. **Results Display**: Show statistics:
   - Number of successfully imported records
   - Number of skipped records (duplicates)
   - Number of errors with details

### Duplicate Prevention:
- Before inserting, system calls `dbProc::getRbfAktByPostfix($numPostfix)`
- If record exists with same `FAKT_NUM_POSTFIX`, it's skipped
- Unique index on `FAKT_NUM_POSTFIX` column ensures database-level uniqueness

## Import Process Flow

1. **User uploads Excel file** via form
2. **System validates** file type (.xls, .xlsx)
3. **PHPExcel reads** the file and extracts data
4. **For each row**:
   - Validate required fields
   - Check for duplicate `FAKT_NUM_POSTFIX`
   - Insert into `rbf_akti` table
5. **If successful** (at least 1 record imported):
   - Generate unique filename
   - Save Excel file to `rbf_act_files/` folder
   - Store file metadata in `rbf_akta_files` table
6. **Display statistics**: success/skip/error counts

## Database Functions

### `dbProc::getRbfAktByPostfix($numPostfix)`
**Purpose**: Check if a record with the given order ID already exists

**Parameters**:
- `$numPostfix` (string) - Order ID to check

**Returns**:
- Array with record data if exists
- `false` if not found

### `dbProc::saveRbfAkt($kwoiKods, $vvNumber, $rbtrKods, $rlttText, $kakvKods, $numPostfix, $workTitle, $piezimes)`
**Purpose**: Insert new RBF act record into `rbf_akti` table

**Parameters**:
- `$kwoiKods` (string) - Employee code
- `$vvNumber` (string) - VV number
- `$rbtrKods` (string) - Department code
- `$rlttText` (string) - Author name
- `$kakvKods` (string) - Act type code
- `$numPostfix` (string) - Order ID (unique)
- `$workTitle` (string) - Work title
- `$piezimes` (string) - Notes (optional)

**Returns**:
- `true` on success
- `false` on failure

### `dbProc::saveRbfAktFile($originalName, $generatedName)`
**Purpose**: Save uploaded Excel file metadata to `rbf_akta_files` table

**Parameters**:
- `$originalName` (string) - Original filename as uploaded by user
- `$generatedName` (string) - System-generated unique filename

**Returns**:
- `true` on success
- `false` on failure

**Generated Filename Format**: `YYYY-MM-DD_HH-ii-ss_[uniqueid].[ext]`

## Usage Instructions

### For Administrators:
1. Navigate to **Options** menu → **Upload RBF akti**
2. Prepare Excel file with correct structure (see table above)
3. Click "Choose File" and select your Excel file
4. Click "Saglabāt" (Save) button
5. Review import results:
   - Green success messages show imported/skipped counts
   - Red error messages show any problems

### Excel File Preparation:
1. Create Excel file (.xls or .xlsx format)
2. First row: Column headers (as specified above)
3. Data rows: Start from row 2
4. Ensure all required fields are filled
5. Make sure `Pasūtījuma ID` (column F) is unique across all imports

### Example Excel Structure:
```
| Darbuzņēmēja kods | VV numurs     | RBF nodaļa | Autors      | Akta veids | Pasūtījuma ID | Darba nosaukums        | Piezīmes |
|-------------------|---------------|------------|-------------|------------|---------------|------------------------|----------|
| 40003524433       | 300000/23-112 | 11223      | Jānis Bērziņš | 50       | ORD-2024-001  | Ceļa remonts A1        | Test     |
| 41503087204       | 300000/24-113 | 308313     | Anna Liepa   | 100       | ORD-2024-002  | Tilta rekonstrukcija   |          |
```

## Security
- Access restricted to Admins only (`userAuthorization::isAdmin()`)
- All database inputs are sanitized using `dbLayer::quote_smart()`
- File type validation prevents uploading non-Excel files
- Unique constraint on `FAKT_NUM_POSTFIX` prevents duplicate data

## Error Handling
- Invalid file type: Shows error message
- Missing required fields: Shows error for specific row
- Database errors: Shows error with row number and details
- Duplicate records: Silently skipped, counted in skip statistics
- PHPExcel exceptions: Caught and displayed with details

## Testing

### Test Scenarios:
1. ✅ Upload valid Excel file with multiple records
2. ✅ Upload file with duplicate `FAKT_NUM_POSTFIX` values
3. ✅ Upload file with empty rows
4. ✅ Upload file with missing required fields
5. ✅ Upload non-Excel file (should fail validation)
6. ✅ Upload empty Excel file
7. ✅ Check statistics display (success/skip/error counts)

## Future Enhancements
- Add data validation against reference tables (employee codes, territory codes, etc.)
- Add preview before import
- Add ability to download sample Excel template
- Add import history/log table
- Add ability to edit imported records
- Add ability to export records back to Excel

## Dependencies
- **PHPExcel Library**: Required for Excel file reading (already in codebase at `libs/PHPExcel/PHPExcel.php`)
- **Form Class**: For form handling and validation
- **dbProc Class**: For database operations
- **userAuthorization Class**: For access control

## SQL Migration
Run `sql/DUIS-549.sql` to create:
- `rbf_akti` table
- All text translations
- Requirements documentation

## Related Functionality
This upload feature is part of the broader RBF (Road Business Framework) module, which includes:
- RBF Acts management (`f.akt.s.30`)
- RBF Works management (`f.akt.s.31`)
- RBF Attachments (`f.akt.s.32`)
- RBF Catalogs (Territories, Employees, Calculations)

